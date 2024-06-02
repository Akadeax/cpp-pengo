#include "SkipLevelCommand.h"

#include "GameManager.h"
#include "GameObject.h"

SkipLevelCommand::SkipLevelCommand(dae::GameObject* pGameManager)
	: Command(pGameManager)
{
}

void SkipLevelCommand::Execute()
{
	m_pGameObject->GetComponent<GameManager>()->AdvanceLevel();
}
