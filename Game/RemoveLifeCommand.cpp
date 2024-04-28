#include "RemoveLifeCommand.h"

#include "GameObject.h"
#include "PlayerController.h"

#include "ServiceLocator.h"
#include "SoundSystem.h"

RemoveLifeCommand::RemoveLifeCommand(dae::GameObject* pObject)
	: Command(pObject)
	, m_pPlayer{ pObject->GetComponent<PlayerController>() }
{
}

void RemoveLifeCommand::Execute()
{
	m_pPlayer->Kill();
	auto& ss = dae::ServiceLocator::GetSoundSystem();
	ss.PlaySound(dae::SoundSystem::SoundType::sfx, 0, 128);
}
