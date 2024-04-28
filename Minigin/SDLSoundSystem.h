#pragma once
#include <memory>

#include "SoundSystem.h"

namespace dae
{
	struct SoundRequest
	{
		SoundSystem::SoundType type;
		SoundSystem::SoundID id;
		int volume;
	};

	class SDLSoundSystem final : public SoundSystem
	{
	public:
		explicit SDLSoundSystem();
		~SDLSoundSystem() override;

		SDLSoundSystem(const SDLSoundSystem&) = delete;
		SDLSoundSystem(SDLSoundSystem&&) noexcept = delete;
		SDLSoundSystem& operator=(const SDLSoundSystem&) = delete;
		SDLSoundSystem& operator=(SDLSoundSystem&&) noexcept = delete;

		SoundID RegisterSound(SoundType type, const std::string& filePath) override;
		void PlaySound(SoundType type, SoundID id, int volume) override;

	private:
		class SDLSoundSystemImpl;
		std::unique_ptr<SDLSoundSystemImpl> m_pImpl;
	};
}