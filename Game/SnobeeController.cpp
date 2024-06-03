#include "SnobeeController.h"

#include <iostream>

#include "Scene.h"
#include "GameManager.h"
#include "GridManager.h"
#include "SceneManager.h"
#include "TextureRenderer.h"
#include "PlayerController.h"
#include "ServiceLocator.h"
#include "SoundEffects.h"

SnobeeController::SnobeeController(dae::GameObject* pParent)
	: Component(pParent)
{
}

void SnobeeController::Ready()
{
	dae::Scene* pScene{ dae::SceneManager::GetInstance().GetCurrentScene() };
	m_pGridManager = pScene->GetGameObjectByTag("GridManager")->GetComponent<GridManager>();
	m_pGameManager = pScene->GetGameObjectByTag("GameManager")->GetComponent<GameManager>();

	for (const dae::GameObject* pGo : pScene->GetGameObjectsByTag("Player"))
	{
		m_PlayerControllers.push_back(pGo->GetComponent<PlayerController>());
	}

	GetParent()->GetComponent<dae::TextureRenderer>()->frame = 7;
}

void SnobeeController::Update()
{
	for (const Block* pBlock : m_pGameManager->GetCurrentlyMovingBlocks())
	{
		const glm::vec2 blockPos{ pBlock->GetParent()->GetTransform().GetWorldPosition() };
		const glm::vec2 self{ GetParent()->GetTransform().GetWorldPosition() };
		const glm::vec2 diff{ blockPos - self };
		const float dist2{ diff.x * diff.x + diff.y * diff.y };

		if (dist2 > DISTANCE_TOLERANCE2) continue;

		Die();
		return;
	}

	for (PlayerController* pPlayer : m_PlayerControllers)
	{
		const glm::vec2 playerPos{ pPlayer->GetParent()->GetTransform().GetWorldPosition() };
		const glm::vec2 self{ GetParent()->GetTransform().GetWorldPosition() };
		const glm::vec2 diff{ playerPos - self };
		const float dist2{ diff.x * diff.x + diff.y * diff.y };

		if (dist2 < DISTANCE_TOLERANCE2)
		{
			if (vulnerable) Die();
			else pPlayer->Kill();
		}
	}
}

void SnobeeController::Die() const
{
	for (auto* pPlayer : m_PlayerControllers)
	{
		pPlayer->IncreaseScore(SCORE_ON_DEATH);
	}

	GetParent()->MarkForDeletion();
	dae::ServiceLocator::GetSoundSystem().PlaySound(dae::SoundSystem::SoundType::sfx, soundEffects::SNOBEE_DEATH, 255);
}
