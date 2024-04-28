#pragma once
#include <string>

namespace dae
{
	class SoundInitializeFailedException {};
	class SoundLoadFailedException {};

	class SoundSystem
	{
	public:
		using SoundID = size_t;
		enum class SoundType
		{
			sfx, music
		};
		virtual ~SoundSystem() = default;

		virtual SoundID RegisterSound(SoundType type, const std::string& filePath) = 0;
		virtual void PlaySound(SoundType type, SoundID id, int volume) = 0;
	};
}