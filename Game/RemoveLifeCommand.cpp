#include "RemoveLifeCommand.h"

#include "GameObject.h"
#include "PlayerController.h"

RemoveLifeCommand::RemoveLifeCommand(dae::GameObject* pObject)
	: Command(pObject)
	, m_pPlayer{ pObject->GetComponent<PlayerController>() }
{
}

void RemoveLifeCommand::Execute()
{
	m_pPlayer->Kill();
}
