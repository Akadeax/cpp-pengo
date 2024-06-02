#include "Block.h"

#include <iostream>

#include "GameObject.h"
#include "GameTime.h"
#include "Transform.h"
#include "GridManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TextureRenderer.h"

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
		m_pGridManager->AddBlock(roundedGridPos, this);

		m_pGridManager->BlockPushEnd.Emit(this);
	}
}

void Block::Ready()
{
	dae::Scene* pScene{ dae::SceneManager::GetInstance().GetCurrentScene() };
	m_pGridManager = pScene->GetGameObjectByTag("GridManager")->GetComponent<GridManager>();
}

void Block::Push(glm::ivec2 dir)
{
	if (!pushable) return;

	dae::Transform& blockTransform{ GetParent()->GetTransform() };
	const glm::vec2 gridPos{ m_pGridManager->WorldToGrid(blockTransform.GetWorldPosition()) };
	m_pGridManager->RemoveBlock(gridPos);

	m_IsPushing = true;
	m_PushDir = dir;

	m_pGridManager->BlockPushStart.Emit(this);
}

void Block::Destroy() const
{
	if (m_Type == Type::diamond) return;

	dae::Transform& blockTransform{ GetParent()->GetTransform() };
	const glm::vec2 gridPos{ m_pGridManager->WorldToGrid(blockTransform.GetWorldPosition()) };
	GetParent()->MarkForDeletion();
	m_pGridManager->RemoveBlock(gridPos);
}

void Block::SetType(Type type)
{
	m_Type = type;
	GetParent()->GetComponent<dae::TextureRenderer>()->frame = static_cast<uint16_t>(m_Type);
}
