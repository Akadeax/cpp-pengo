#pragma once
#include "AnimatedTextureRenderer.h"
#include "PlayerState.h"
#include "PlayerStateMachine.h"

class PlayerIdleState final : public PlayerState
{
public:
	PlayerIdleState(
		PlayerController* pPlayerController,
		PlayerStateMachine* pStateMachine, 
		dae::AnimatedTextureRenderer* pRenderer, 
		dae::StateID moveStateID,
		dae::StateID interactStateID
	);

	void OnEnter() override;
	void OnExit() override;

private:
	dae::StateID m_MoveStateID;
	dae::StateID m_InteractStateID;

	dae::ConnectionID m_OnMoveInputConn{};
	dae::ConnectionID m_OnInteractInputConn{};

	dae::AnimationID m_IdleUp{};
	dae::AnimationID m_IdleRight{};
	dae::AnimationID m_IdleDown{};
	dae::AnimationID m_IdleLeft{};
};

