#include "ServiceLocator.h"

void dae::ServiceLocator::RegisterSoundSystem(std::unique_ptr<SoundSystem>&& ss)
{
	m_SoundSystemInstance = std::move(ss);
}
