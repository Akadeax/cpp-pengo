#include "Block.h"

#include <iostream>

#include "GameObject.h"
#include "GameTime.h"
#include "Transform.h"
#include "GridManager.h"
#include "Scene.h"

Block::Block(dae::GameObject* pParent)
	: Component(pParent)
{
}

void Block::Update()
{
	if (!m_IsPushing) return;

	dae::Transform& trans{ GetParent()->GetTransform() };

	trans.Translate(
		glm::vec2{ m_PushDir.x, m_PushDir.y } * m_PushSpeed * dae::GameTime::GetInstance().GetDeltaTime()
	);

	const glm::vec2 gridPos{ m_pGridManager->WorldToGrid(trans.GetWorldPosition()) };

	const glm::vec2 pushDirGridPos{
		gridPos + glm::vec2{ m_PushDir.x, m_PushDir.y }
	};

	if (m_pGridManager->HasBlock(pushDirGridPos) || !m_pGridManager->IsGridPositionValid(pushDirGridPos))
	{
		m_IsPushing = false;
		const glm::ivec2 roundedGridPos{ lround(gridPos.x), lround(gridPos.y) };
		const glm::vec2 roundedGridToWorld{ m_pGridManager->GridToWorld(roundedGridPos, false) };

		trans.SetLocalPosition(roundedGridToWorld - GetParent()->GetParent()->GetTransform().GetWorldPosition());
		m_pGridManager->AddBlock(roundedGridPos, GetParent());
	}
}

void Block::Ready()
{
	dae::Scene* pScene{ dae::SceneManager::GetInstance().GetCurrentScene() };
	m_pGridManager = pScene->GetGameObjectByTag("GridManager")->GetComponent<GridManager>();
}

void Block::Push(glm::ivec2 dir)
{
	dae::Transform& blockTransform{ GetParent()->GetTransform() };
	const glm::vec2 gridPos{ m_pGridManager->WorldToGrid(blockTransform.GetWorldPosition()) };
	m_pGridManager->RemoveBlock(gridPos);

	m_IsPushing = true;
	m_PushDir = dir;
}

void Block::Destroy() const
{
	dae::Transform& blockTransform{ GetParent()->GetTransform() };
	const glm::vec2 gridPos{ m_pGridManager->WorldToGrid(blockTransform.GetWorldPosition()) };
	GetParent()->MarkForDeletion();
	m_pGridManager->RemoveBlock(gridPos);
}
