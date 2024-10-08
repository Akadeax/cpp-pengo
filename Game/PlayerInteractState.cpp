#include "PlayerInteractState.h"

#include <iostream>
#include <SDL_syswm.h>
#include <glm/gtc/epsilon.hpp>

#include "AnimatedTextureRenderer.h"
#include "GameManager.h"
#include "GameObject.h"
#include "GameTime.h"
#include "GridManager.h"
#include "PlayerController.h"
#include "PlayerStateMachine.h"
#include "Scene.h"
#include "SceneManager.h"
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


	const dae::Scene* pScene{ dae::SceneManager::GetInstance().GetCurrentScene() };
	const GridManager* pGridManager{ pScene->GetGameObjectByTag("GridManager")->GetComponent<GridManager>() };

	const dae::Transform& playerTransform{ GetStateMachine()->GetParent()->GetTransform() };
	const glm::ivec2 dir{ GetPlayerController()->FacingDir };
	const glm::vec2 targetGridSpace{
		pGridManager->WorldToGrid(playerTransform.GetLocalPosition()) + glm::vec2{ dir.x, dir.y }
	};

	if (!pGridManager->IsGridPositionValid(targetGridSpace))
	{
		GameManager* pGameManager{ pScene->GetGameObjectByTag("GameManager")->GetComponent<GameManager>() };
		pGameManager->StunWall(GetPlayerController()->FacingDir);
		return;
	}

	Block* targetBlock{ pGridManager->GetBlock(targetGridSpace) };
	if (targetBlock == nullptr) return;

	const glm::vec2 targetGridSpaceBehind{ targetGridSpace + glm::vec2{ dir.x, dir.y } };
	Block* targetBlockBehind{ pGridManager->GetBlock(targetGridSpaceBehind) };

	if (targetBlockBehind != nullptr || !pGridManager->IsGridPositionValid(targetGridSpaceBehind))
	{
		targetBlock->Destroy();
	}
	else
	{
		targetBlock->Push(dir);
	}
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
