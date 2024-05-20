#include "PlayerInteractCommand.h"

#include "GameObject.h"
#include "PlayerStateMachine.h"

PlayerInteractCommand::PlayerInteractCommand(dae::GameObject* pPlayer)
	: Command(pPlayer)
{
	m_pPlayerStateMachine = pPlayer->GetComponent<PlayerStateMachine>();
}

void PlayerInteractCommand::Execute()
{
	m_pPlayerStateMachine->OnInteractInput.Emit();
}
