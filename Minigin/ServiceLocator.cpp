#include "ServiceLocator.h"

#include "NullResourceSystem.h"
#include "NullSoundSystem.h"

std::unique_ptr<dae::SoundSystem> dae::ServiceLocator::m_SoundSystemInstance
	{ std::make_unique<NullSoundSystem>() };

std::unique_ptr<dae::ResourceSystem> dae::ServiceLocator::m_ResourceSystemInstance
	{ std::make_unique<NullResourceSystem>() };

dae::SoundSystem& dae::ServiceLocator::GetSoundSystem()
{
	return *m_SoundSystemInstance;
}

void dae::ServiceLocator::RegisterSoundSystem(std::unique_ptr<SoundSystem>&& ss)
{
	m_SoundSystemInstance = std::move(ss);
}

dae::ResourceSystem& dae::ServiceLocator::GetResourceSystem()
{
	return *m_ResourceSystemInstance;
}

void dae::ServiceLocator::RegisterResourceSystem(std::unique_ptr<ResourceSystem>&& rs)
{
	m_ResourceSystemInstance = std::move(rs);
}
