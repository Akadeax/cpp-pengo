#pragma once
#include "State.h"
#include "StateMachine.h"

class PlayerController;

class PlayerMoveState final : public dae::State
{
public:
	PlayerMoveState(dae::StateMachine* pStateMachine, PlayerController* pPlayer, dae::StateID idleStateID);

	void OnEnter() override;
	void Update() override;

private:
	PlayerController* m_pPlayerController;
	dae::StateID m_IdleStateID;
};

