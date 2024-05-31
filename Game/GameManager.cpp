#include "GameManager.h"

#include <algorithm>
#include <iostream>
#include <random>

#include "Scene.h"
#include "GridManager.h"
#include "ResourceSystem.h"
#include "ServiceLocator.h"
#include "TextureRenderer.h"
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


	std::unique_ptr timer{ std::make_unique<dae::Timer>(GetParent(), 2.f, true) };
	m_pEnemyTimer = timer.get();
	timer->Timeout.Connect([this] { RefillEnemiesFromUnhatched(); });
	GetParent()->AddComponent(std::move(timer));

	m_pSnobeeTexture = dae::ServiceLocator::GetResourceSystem().LoadTexture("Data/snobee_green.png");
}

void GameManager::RefillEnemiesFromUnhatched()
{
	std::vector unhatchedBlocks{ m_pGridManager->GetBlocksOfType(Block::Type::unhatched) };

	if (unhatchedBlocks.empty()) return;

	std::random_device rd;
	std::mt19937 gen{ rd() };

	std::ranges::shuffle(unhatchedBlocks, gen);

	int currentEnemyIndex{ 0 };
	while (m_CurrentEnemyCount < MAX_ENEMIES)
	{
		std::cout << "spawning enemy\n";
		ReplaceBlockWithEnemy(unhatchedBlocks[currentEnemyIndex++]);
	}
}

void GameManager::ReplaceBlockWithEnemy(const Block* block)
{
	std::unique_ptr pSnobee{ std::make_unique<dae::GameObject>() };
	pSnobee->AddComponent(std::make_unique<dae::TextureRenderer>(pSnobee.get(), m_pSnobeeTexture, 5, 8));

	std::unique_ptr pSnobeeController{ std::make_unique<SnobeeController>(pSnobee.get()) };
	pSnobee->AddComponent(std::move(pSnobeeController));

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
}

void GameManager::OnEnemyMarkedForDeletion(const dae::GameObject*)
{
	--m_CurrentEnemyCount;
	RefillEnemiesFromUnhatched();

	if (m_CurrentEnemyCount == 0)
	{
		std::cout << "You win level :)\n";
	}
}