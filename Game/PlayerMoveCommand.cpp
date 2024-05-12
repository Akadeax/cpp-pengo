#include "PlayerMoveCommand.h"

#include "GameObject.h"
#include "PlayerController.h"

PlayerMoveCommand::PlayerMoveCommand(dae::GameObject* pPlayer, glm::vec2 dir)
	: Command(pPlayer)
	, m_Dir{ dir }
{
	m_pPlayerController = pPlayer->GetComponent<PlayerController>();
}

void PlayerMoveCommand::Execute()
{
	m_pPlayerController->SetMoveDirection(m_Dir);
}
