#include "PlayerInteractState.h"

#include <iostream>

#include "AnimatedTextureRenderer.h"
#include "GameObject.h"
#include "GameTime.h"
#include "GridManager.h"
#include "PlayerController.h"
#include "PlayerStateMachine.h"
#include "Scene.h"
#include "Transform.h"

PlayerInteractState::PlayerInteractState(
	PlayerController* pPlayerController, 
	PlayerStateMachine* pStateMachine,
	dae::AnimatedTextureRenderer* pRenderer,
	dae::StateID idleStateID
)
	: PlayerState(pPlayerController, pStateMachine, pRenderer)
	, m_IdleStateID{ idleStateID }
{
	m_InteractUp = GetRenderer()->   AddAnimation({ 0.3f, { 12, 13 } });
	m_InteractRight = GetRenderer()->AddAnimation({ 0.3f, { 14, 15 } });
	m_InteractDown = GetRenderer()-> AddAnimation({ 0.3f, { 8, 9 } });
	m_InteractLeft = GetRenderer()-> AddAnimation({ 0.3f, { 10, 11 } });
}

void PlayerInteractState::OnEnter()
{
	m_TimeSinceEnter = 0.f;

	GetRenderer()->SetDirectionalAnimation(
		GetPlayerController()->FacingDir,
		m_InteractUp,
		m_InteractRight,
		m_InteractDown,
		m_InteractLeft
	);


	dae::Scene* pScene{ dae::SceneManager::GetInstance().GetCurrentScene() };
	const GridManager* pGridManager{ pScene->GetGameObjectByTag("GridManager")->GetComponent<GridManager>() };

	const dae::Transform& playerTransform{ GetStateMachine()->GetParent()->GetTransform() };
	const glm::ivec2 dir{ GetPlayerController()->FacingDir };
	const glm::vec2 targetGridSpace{
		pGridManager->WorldToGrid(playerTransform.GetLocalPosition()) + glm::vec2{ dir.x, dir.y }
	};

	std::cout << (pGridManager->HasBlock(targetGridSpace)) << '\n';
}

void PlayerInteractState::Update()
{
	const float delta{dae::GameTime::GetInstance().GetDeltaTime() };
	if (m_TimeSinceEnter + delta >= m_InteractionTime)
	{
		GetStateMachine()->SetState(m_IdleStateID);
		return;
	}

	m_TimeSinceEnter += delta;
}
