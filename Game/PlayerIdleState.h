#pragma once
#include "State.h"
#include "StateMachine.h"

class PlayerController;

class PlayerIdleState final : public dae::State
{
public:
	PlayerIdleState(dae::StateMachine* pStateMachine, PlayerController* pPlayer, dae::StateID moveStateID);

	void OnEnter() override;
	void Update() override;

private:
	PlayerController* m_pPlayerController;
	dae::StateID m_MoveStateID;
};

