#include "IncreaseScoreCommand.h"

#include "GameObject.h"
#include "PlayerController.h"

IncreaseScoreCommand::IncreaseScoreCommand(dae::GameObject* pObject)
	: Command(pObject)
	, m_pPlayer{ pObject->GetComponent<PlayerController>() }
{
}

void IncreaseScoreCommand::Execute()
{
	m_pPlayer->IncreaseScore(100);
}
