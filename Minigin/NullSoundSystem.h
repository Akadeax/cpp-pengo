#pragma once
#include "SoundSystem.h"

namespace dae
{
	class NullSoundSystem final : public SoundSystem
	{
	public:
		NullSoundSystem() = default;
		~NullSoundSystem() override = default;

		NullSoundSystem(const NullSoundSystem&) = delete;
		NullSoundSystem(NullSoundSystem&&) noexcept = delete;
		NullSoundSystem& operator= (const NullSoundSystem&) = delete;
		NullSoundSystem& operator= (const NullSoundSystem&&) noexcept = delete;

		SoundID RegisterSound(SoundType, const std::string&) override { return 0; }
		void PlaySound(SoundType, SoundID, int) override {}
		void StopMusic() override {}
		void MuteSound() override {}
		void UnmuteSound() override {}
	};
}

