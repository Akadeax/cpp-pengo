#include "SnobeeController.h"

#include <iostream>

#include "Scene.h"
#include "GameManager.h"
#include "GridManager.h"
#include "TextureRenderer.h"

SnobeeController::SnobeeController(dae::GameObject* pParent)
	: Component(pParent)
{
}

void SnobeeController::Ready()
{
	dae::Scene* pScene{ dae::SceneManager::GetInstance().GetCurrentScene() };
	m_pGridManager = pScene->GetGameObjectByTag("GridManager")->GetComponent<GridManager>();
	m_pGameManager = pScene->GetGameObjectByTag("GameManager")->GetComponent<GameManager>();

	GetParent()->GetComponent<dae::TextureRenderer>()->frame = 7;
}

void SnobeeController::Update()
{
	for (const Block* block : m_pGameManager->GetCurrentlyMovingBlocks())
	{
		const glm::vec2 blockPos{ block->GetParent()->GetTransform().GetLocalPosition() };
		const glm::vec2 local{ GetParent()->GetTransform().GetLocalPosition() };
		const glm::vec2 diff{ blockPos - local };
		const float dist2{ diff.x * diff.x + diff.y * diff.y };

		if (dist2 < MOVING_BLOCK_DISTANCE_TOLERANCE2)
		{
			GetParent()->MarkForDeletion();
		}
	}
}
