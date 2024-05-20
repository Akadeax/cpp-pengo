#include "PlayerMoveState.h"

#include "PlayerController.h"

#pragma warning(push, 0)
#include <glm/gtx/string_cast.hpp>
#pragma warning(pop)

#include "GameObject.h"
#include "GameTime.h"
#include "PlayerStateMachine.h"

PlayerMoveState::PlayerMoveState(
	PlayerController* pPlayerController, 
	PlayerStateMachine* pStateMachine,
	dae::AnimatedTextureRenderer* pRenderer,
	dae::StateID idleStateID
)
	: PlayerState(pPlayerController, pStateMachine, pRenderer)
	, m_IdleStateID{ idleStateID }
{
	m_MoveUp = GetRenderer()->   AddAnimation({ 0.4f, { 4, 5 } });
	m_MoveRight = GetRenderer()->AddAnimation({ 0.4f, { 6, 7 } });
	m_MoveDown = GetRenderer()-> AddAnimation({ 0.4f, { 0, 1 } });
	m_MoveLeft = GetRenderer()-> AddAnimation({ 0.4f, { 2, 3 } });
}

void PlayerMoveState::OnEnter()
{
	m_TimeSinceEnter = 0.f;
	m_MoveStartPos = GetPlayerController()->GetParent()->GetTransform().GetWorldPosition();
	GetRenderer()->SetDirectionalAnimation(
		GetPlayerController()->FacingDir,
		m_MoveUp,
		m_MoveRight,
		m_MoveDown,
		m_MoveLeft
	);
}

void PlayerMoveState::Update()
{
	m_TimeSinceEnter += dae::GameTime::GetInstance().GetDeltaTime() / m_MoveTime;

	if (m_TimeSinceEnter >= 1.f)
	{
		GetPlayerController()->GetParent()->GetTransform().SetLocalPosition(
			GetPlayerController()->MovementTarget
		);

		GetStateMachine()->SetState(m_IdleStateID);
	}
	else
	{
		GetPlayerController()->GetParent()->GetTransform().SetLocalPosition(
			mix(m_MoveStartPos, GetPlayerController()->MovementTarget, m_TimeSinceEnter)
		);
	}
}
