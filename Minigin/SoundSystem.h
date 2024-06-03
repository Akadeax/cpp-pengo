#pragma once
#include <string>

#define DAE_SOUND_VAR(name) inline dae::SoundID name{ std::numeric_limits<size_t>::max() }

namespace dae
{
	class SoundInitializeFailedException {};
	class SoundLoadFailedException {};

	using SoundID = size_t;

	class SoundSystem
	{
	public:
		enum class SoundType
		{
			sfx, music
		};
		virtual ~SoundSystem() = default;

		virtual SoundID RegisterSound(SoundType type, const std::string& filePath) = 0;
		virtual void PlaySound(SoundType type, SoundID id, int volume) = 0;

		virtual void StopMusic() = 0;

		virtual void MuteSound() = 0;
		virtual void UnmuteSound() = 0;
	};
}