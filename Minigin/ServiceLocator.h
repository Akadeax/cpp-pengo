#pragma once
#include <memory>

#include "NullSoundSystem.h"
#include "SoundSystem.h"

namespace dae
{
	class ServiceLocator final
	{
	public:
		ServiceLocator() = delete;

		static SoundSystem& GetSoundSystem() { return *m_SoundSystemInstance; }
		static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& ss);

	private:
		inline static std::unique_ptr<SoundSystem> m_SoundSystemInstance{ std::make_unique<NullSoundSystem>() };
	};
}
