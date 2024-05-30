#pragma once
#include <memory>

namespace dae
{
	class ResourceSystem;
	class SoundSystem;

	class ServiceLocator final
	{
	public:
		ServiceLocator() = delete;

		static SoundSystem& GetSoundSystem();
		static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& ss);

		static ResourceSystem& GetResourceSystem();
		static void RegisterResourceSystem(std::unique_ptr<ResourceSystem>&& rs);

	private:
		static std::unique_ptr<SoundSystem> m_SoundSystemInstance;
		static std::unique_ptr<ResourceSystem> m_ResourceSystemInstance;
	};
}
