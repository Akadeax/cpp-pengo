#include "PlayerIdleState.h"

#include <iostream>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtx/norm.inl>

#include "GameObject.h"
#include "GridManager.h"
#include "PlayerController.h"
#include "Scene.h"

#pragma warning(push, 0)
#include <glm/gtx/string_cast.hpp>
#pragma warning(pop)

#include "AnimatedTextureRenderer.h"

PlayerIdleState::PlayerIdleState(
	PlayerController* pPlayerController,
	PlayerStateMachine* pStateMachine,
	dae::AnimatedTextureRenderer* pRenderer,
	dae::StateID moveStateID,
	dae::StateID interactStateID
)
	: PlayerState(pPlayerController, pStateMachine, pRenderer)
	, m_MoveStateID{ moveStateID }
	, m_InteractStateID{ interactStateID }
{
	m_IdleUp = GetRenderer()->   AddAnimation({ 1.f, { 4 } });
	m_IdleRight = GetRenderer()->AddAnimation({ 1.f, { 7 } });
	m_IdleDown = GetRenderer()-> AddAnimation({ 1.f, { 0 } });
	m_IdleLeft = GetRenderer()-> AddAnimation({ 1.f, { 3 } });
}

void PlayerIdleState::OnEnter()
{
	GetRenderer()->SetDirectionalAnimation(
		GetPlayerController()->FacingDir,
		m_IdleUp,
		m_IdleRight, 
		m_IdleDown, 
		m_IdleLeft
	);

	m_OnMoveInputConn = GetStateMachine()->OnMoveInput.Connect([this](glm::ivec2 dir)
		{
			dae::Scene* pScene{ dae::SceneManager::GetInstance().GetCurrentScene() };
			const GridManager* pGridManager{ pScene->GetGameObjectByTag("GridManager")->GetComponent<GridManager>() };

			GetPlayerController()->FacingDir = dir;
			GetRenderer()->SetDirectionalAnimation(
				GetPlayerController()->FacingDir,
				m_IdleUp,
				m_IdleRight,
				m_IdleDown,
				m_IdleLeft
			);

			const dae::Transform& playerTransform{ GetStateMachine()->GetParent()->GetTransform() };
			const glm::vec2 targetGridSpace{
				pGridManager->WorldToGrid(playerTransform.GetLocalPosition()) + glm::vec2{ dir.x, dir.y }
			};

			if (pGridManager->HasBlock(targetGridSpace)) return;
			if (!pGridManager->IsGridPositionValid(targetGridSpace)) return;

			GetPlayerController()->MovementTarget = pGridManager->GridToWorld(targetGridSpace);

			GetStateMachine()->SetState(m_MoveStateID);
		});

	m_OnInteractInputConn = GetStateMachine()->OnInteractInput.Connect([this]
		{
			GetStateMachine()->SetState(m_InteractStateID);
		});
}

void PlayerIdleState::OnExit()
{
	GetStateMachine()->OnMoveInput.Disconnect(m_OnMoveInputConn);
	GetStateMachine()->OnInteractInput.Disconnect(m_OnInteractInputConn);
}
