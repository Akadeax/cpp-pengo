#include "SnobeeChaseState.h"

#include <iostream>

#include "AnimatedTextureRenderer.h"
#include "GameObject.h"
#include "GameTime.h"
#include "Scene.h"
#include "GridManager.h"
#include "SceneManager.h"
#include "SnobeeController.h"
#include "SnobeeStateMachine.h"

SnobeeChaseState::SnobeeChaseState(
	SnobeeController* pSnobeeController,
	SnobeeStateMachine* pStateMachine,
	dae::AnimatedTextureRenderer* pRenderer
)
	: SnobeeState(pSnobeeController, pStateMachine, pRenderer)
{
	dae::Scene* pScene{ dae::SceneManager::GetInstance().GetCurrentScene() };
	m_pGridManager = pScene->GetGameObjectByTag("GridManager")->GetComponent<GridManager>();

	m_ChaseUp = GetRenderer()->   AddAnimation({ .3f, { 12, 13 } });
	m_ChaseRight = GetRenderer()->AddAnimation({ .3f, { 14, 15 } });
	m_ChaseDown = GetRenderer()-> AddAnimation({ .3f, { 8, 9 } });
	m_ChaseLeft = GetRenderer()-> AddAnimation({ .3f, { 10, 11 } });
}

void SnobeeChaseState::OnEnter()
{
	m_MoveStartPos = GetSnobeeController()->GetParent()->GetTransform().GetLocalPosition();
	m_MoveTargetPos = m_MoveStartPos;
	m_MoveDir = glm::ivec2{ 0, -1 };
}

void SnobeeChaseState::Update()
{
	if (m_TimeUntilNextMove <= 0.f)
	{
		GetSnobeeController()->GetParent()->GetTransform().SetLocalPosition(m_MoveTargetPos);
		m_MoveStartPos = m_MoveTargetPos;

		// convert all our positions into grid coordinates so we can check for blocks
		const glm::vec2 startAsGrid{ m_pGridManager->LocalToGrid(m_MoveStartPos, false) };
		glm::vec2 targetAsGrid{ startAsGrid + glm::vec2{ m_MoveDir.x, m_MoveDir.y } };

		// if there is an obstacle, turn around
		if (!m_pGridManager->IsGridPositionValid(targetAsGrid) || m_pGridManager->HasBlock(targetAsGrid))
		{
			m_MoveDir.y *= -1;
			targetAsGrid = startAsGrid + glm::vec2{ m_MoveDir.x, m_MoveDir.y };
		}

		
		m_MoveTargetPos = m_pGridManager->GridToLocal(targetAsGrid, false);

		m_TimeUntilNextMove = m_MoveTime;
		GetRenderer()->SetDirectionalAnimation(
			m_MoveDir,
			m_ChaseUp,
			m_ChaseRight,
			m_ChaseDown,
			m_ChaseLeft
		);

		return;
	}

	m_TimeUntilNextMove -= dae::GameTime::GetInstance().GetDeltaTime();

	const float lerpFactor{ (m_MoveTime - m_TimeUntilNextMove) / m_MoveTime };
	GetSnobeeController()->GetParent()->GetTransform().SetLocalPosition(
		mix(m_MoveStartPos, m_MoveTargetPos, lerpFactor)
	);
}
