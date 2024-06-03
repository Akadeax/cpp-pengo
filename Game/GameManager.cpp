#include "GameManager.h"

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <random>
#include <sstream>
#include <glm/gtc/epsilon.hpp>

#include "AnimatedTextureRenderer.h"
#include "GameObject.h"
#include "Scene.h"
#include "GridManager.h"
#include "InputManager.h"
#include "PlayerController.h"
#include "ResourceSystem.h"
#include "SaveData.h"
#include "SceneManager.h"
#include "Scenes.h"
#include "ServiceLocator.h"
#include "SnobeeStateMachine.h"
#include "SoundEffects.h"
#include "Timer.h"

GameManager::GameManager(dae::GameObject* pParent)
	: Component(pParent)
{
}

void GameManager::Ready()
{
	dae::Scene* pScene{ dae::SceneManager::GetInstance().GetCurrentScene() };
	m_pGridManager = pScene->GetGameObjectByTag("GridManager")->GetComponent<GridManager>();

	m_pGridManager->BlockPushStart.Connect([this](Block* block) { OnBlockPushStart(block); });
	m_pGridManager->BlockPushEnd.Connect([this](Block* block) { OnBlockPushEnd(block); });


	std::unique_ptr timer{ std::make_unique<dae::Timer>(GetParent(), 3.f, true) };
	m_pEnemyTimer = timer.get();
	timer->Timeout.Connect([this]
	{
		RefillEnemiesFromUnhatched();
		dae::ServiceLocator::GetSoundSystem().PlaySound(dae::SoundSystem::SoundType::music, soundEffects::SONG, 255);
	});
	GetParent()->AddComponent(std::move(timer));

	m_pSnobeeTexture = dae::ServiceLocator::GetResourceSystem().LoadTexture("Data/snobee_green.png");

	dae::ServiceLocator::GetSoundSystem().PlaySound(dae::SoundSystem::SoundType::sfx, soundEffects::PLAYER_START, 255);
}

void GameManager::AdvanceLevel()
{
	SaveData::GetInstance().SaveCrossLevelData(dae::SceneManager::GetInstance().GetCurrentScene());

	const int currentSceneID{ dae::SceneManager::GetInstance().GetCurrentScene()->GetID() };

	std::stringstream ss;
	ss << "Data/Levels/" << currentSceneID + 1 << ".json";
	std::string filePath{ ss.str() };


	if (!std::filesystem::exists(filePath))
	{
		dae::SceneManager::GetInstance().QueueSceneLoadForEndOfFrame(CreateFirstGameScene);
	}
	else
	{
		dae::SceneManager::GetInstance().QueueSceneLoadForEndOfFrame([filePath, currentSceneID]() -> std::unique_ptr<dae::Scene>
			{
				return CreateGameScene(filePath, currentSceneID + 1);
			});
	}
}

void GameManager::RefillEnemiesFromUnhatched()
{
	std::vector unhatchedBlocks{ m_pGridManager->GetBlocksOfType(Block::Type::unhatched) };

	if (unhatchedBlocks.empty()) return;

	std::random_device rd;
	std::mt19937 gen{ rd() };

	std::ranges::shuffle(unhatchedBlocks, gen);

	size_t currentEnemyIndex{ 0 };
	while (m_CurrentEnemyCount < MAX_ENEMIES)
	{
		if (currentEnemyIndex >= unhatchedBlocks.size()) return;

		ReplaceBlockWithEnemy(unhatchedBlocks[currentEnemyIndex++]);
	}
}

void GameManager::ReplaceBlockWithEnemy(const Block* block)
{
	std::unique_ptr pSnobee{ std::make_unique<dae::GameObject>() };
	pSnobee->AddComponent(std::make_unique<dae::AnimatedTextureRenderer>(
		pSnobee.get(), m_pSnobeeTexture, 5, 8)
	);

	pSnobee->AddComponent(std::make_unique<SnobeeController>(pSnobee.get()));
	pSnobee->AddComponent(std::make_unique<SnobeeStateMachine>(pSnobee.get()));

	pSnobee->GetTransform().SetLocalPosition(block->GetParent()->GetTransform().GetLocalPosition());
	pSnobee->MarkedForDeletion.Connect([this](const dae::GameObject* go) { OnEnemyMarkedForDeletion(go); });
	GetParent()->AttachChild(std::move(pSnobee));

	const glm::vec2 currentBlockPos{ block->GetParent()->GetTransform().GetWorldPosition() };
	const glm::vec2 currentGridPos{ m_pGridManager->WorldToGrid(currentBlockPos) };
	block->GetParent()->MarkForDeletion();
	m_pGridManager->RemoveBlock(currentGridPos);

	++m_CurrentEnemyCount;
}

void GameManager::OnBlockPushStart(Block* block)
{
	m_CurrentlyMovingBlocks.push_back(block);
}

void GameManager::OnBlockPushEnd(Block* block)
{
	std::erase(m_CurrentlyMovingBlocks, block);

	if (block->GetType() != Block::Type::diamond) return;

	CheckDiamondBlocks();
}

void GameManager::CheckDiamondBlocks()
{
	// Find the largest x and y distance of all diamond blocks;
	// if they're in a straight line the (x/y) distance will be (2/0) or (0/2)

	// convert from block to its grid position
	auto getPosFromBlock{ [this](const Block* pBlock) -> glm::vec2
	{
		return m_pGridManager->LocalToGrid(pBlock->GetParent()->GetTransform().GetLocalPosition(), false);
	} };
	auto getXFromBlock{ [this, &getPosFromBlock](const Block* pBlock) -> float
		{
			return getPosFromBlock(pBlock).x;
		} };
	auto getYFromBlock{ [this, &getPosFromBlock](const Block* pBlock) -> float
		{
			return getPosFromBlock(pBlock).y;
		} };

	std::vector<Block*> diamondBlocks{ m_pGridManager->GetBlocksOfType(Block::Type::diamond) };
	
	// find largest y distance between blocks
	const std::ranges::minmax_result yMinMax{
		std::ranges::minmax(diamondBlocks, std::less{}, getYFromBlock)
	};
	const float yMaxDistance{ getYFromBlock(yMinMax.max) - getYFromBlock(yMinMax.min) };

	// find largest x distance between blocks
	const std::ranges::minmax_result xMinMax{
	std::ranges::minmax(diamondBlocks, std::less{}, getXFromBlock)
	};
	const float xMaxDistance{ getXFromBlock(xMinMax.max) - getXFromBlock(xMinMax.min) };

	const bool isVerticalRow{
		glm::epsilonEqual(xMaxDistance, 0.f, 0.1f) && glm::epsilonEqual(yMaxDistance, 2.f, 0.1f)
	};
	const bool isHorizontalRow{
		glm::epsilonEqual(yMaxDistance, 0.f, 0.1f) && glm::epsilonEqual(xMaxDistance, 2.f, 0.1f)
	};

	const bool anyAtEdge{ std::ranges::any_of(diamondBlocks, [](glm::vec2 blockPos)
	{
		const bool anyX{ glm::epsilonEqual(std::abs(blockPos.x), static_cast<float>(GridManager::GRID_WIDTH / 2), 0.1f) };
		const bool anyY{ glm::epsilonEqual(std::abs(blockPos.y), static_cast<float>(GridManager::GRID_HEIGHT / 2), 0.1f) };
		return anyX || anyY;
	}, getPosFromBlock)};

	if (!isVerticalRow && !isHorizontalRow) return;

	for (const std::unique_ptr<dae::GameObject>& child : GetParent()->GetChildren())
	{
		child->GetComponent<SnobeeStateMachine>()->Stun();
	}

	const int scoreAmount{ anyAtEdge ? DIAMOND_BLOCKS_COMBINE_POINTS_WALL : DIAMOND_BLOCKS_COMBINE_POINTS_FREE };

	const dae::Scene* pScene{ dae::SceneManager::GetInstance().GetCurrentScene() };
	for (const dae::GameObject* pPlayer : pScene->GetGameObjectsByTag("Player"))
	{
		pPlayer->GetComponent<PlayerController>()->IncreaseScore(scoreAmount);
	}

	for (Block* pDiamond : diamondBlocks)
	{
		pDiamond->pushable = false;
	}
}

void GameManager::OnEnemyMarkedForDeletion(const dae::GameObject*)
{
	--m_CurrentEnemyCount;
	RefillEnemiesFromUnhatched();

	if (m_CurrentEnemyCount == 0)
	{
		std::unique_ptr timer{ std::make_unique<dae::Timer>(GetParent(), 3.f, true) };
		m_pEnemyTimer = timer.get();
		timer->Timeout.Connect([this]
			{
				AdvanceLevel();
			});
		GetParent()->AddComponent(std::move(timer));

		dae::ServiceLocator::GetSoundSystem().StopMusic();
		dae::ServiceLocator::GetSoundSystem().PlaySound(dae::SoundSystem::SoundType::sfx, soundEffects::PLAYER_CLEAR, 255);
	}
}
