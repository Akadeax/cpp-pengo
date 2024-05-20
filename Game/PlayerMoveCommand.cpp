#include "PlayerMoveCommand.h"

#include "GameObject.h"
#include "PlayerStateMachine.h"

PlayerMoveCommand::PlayerMoveCommand(dae::GameObject* pPlayer, glm::ivec2 dir)
	: Command(pPlayer)
	, m_Dir{ dir }
{
	m_pPlayerStateMachine = pPlayer->GetComponent<PlayerStateMachine>();
}

void PlayerMoveCommand::Execute()
{
	m_pPlayerStateMachine->OnMoveInput.Emit(m_Dir);
}
