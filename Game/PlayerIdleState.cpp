#include "PlayerIdleState.h"

#include <iostream>

#include "PlayerController.h"
#include "StateMachine.h"


PlayerIdleState::PlayerIdleState(dae::StateMachine* pStateMachine, PlayerController* pPlayer, dae::StateID moveStateID)
	: State(pStateMachine)
	, m_pPlayerController{ pPlayer }
	, m_MoveStateID{ moveStateID }
{
}

void PlayerIdleState::OnEnter()
{
	std::cout << "Entered idle\n";
}

void PlayerIdleState::Update()
{
	if (m_pPlayerController->IsMoving())
	{
		GetStateMachine()->SetState(m_MoveStateID);
	}
}
