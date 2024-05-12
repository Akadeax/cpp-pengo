#include "PlayerMoveState.h"

#include <iostream>

#include "PlayerController.h"
#include "StateMachine.h"

PlayerMoveState::PlayerMoveState(dae::StateMachine* pStateMachine, PlayerController* pPlayer, dae::StateID idleStateID)
	: State(pStateMachine)
	, m_pPlayerController{ pPlayer }
	, m_IdleStateID{ idleStateID }
{
}

void PlayerMoveState::OnEnter()
{
	std::cout << "Entered move\n";
}

void PlayerMoveState::Update()
{
	if (!m_pPlayerController->IsMoving())
	{
		GetStateMachine()->SetState(m_IdleStateID);
	}
}
