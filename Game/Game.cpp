#define SDL_MAIN_HANDLED
#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#endif
#endif

#include "SaveData.h"
#include "SDLResourceSystem.h"
#include "SDLSoundSystem.h"
#include "ServiceLocator.h"
#include "Minigin/Minigin.h"
#include "Scenes.h"
#include "SoundEffects.h"
#include "SaveData.h"

void Load()
{
	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::SDLSoundSystem>());

	dae::SoundSystem& sound{ dae::ServiceLocator::GetSoundSystem() };
	soundEffects::BLOCK_BREAK = sound.RegisterSound(dae::SoundSystem::SoundType::sfx, "Data/Sound/block_break.mp3");
	soundEffects::BLOCK_STOP = sound.RegisterSound(dae::SoundSystem::SoundType::sfx, "Data/Sound/block_stop.mp3");
	soundEffects::PLAYER_CLEAR = sound.RegisterSound(dae::SoundSystem::SoundType::sfx, "Data/Sound/player_clear.mp3");
	soundEffects::PLAYER_DEATH = sound.RegisterSound(dae::SoundSystem::SoundType::sfx, "Data/Sound/player_death.mp3");
	soundEffects::PLAYER_LOSE = sound.RegisterSound(dae::SoundSystem::SoundType::sfx, "Data/Sound/player_lose.mp3");
	soundEffects::PLAYER_START = sound.RegisterSound(dae::SoundSystem::SoundType::sfx, "Data/Sound/player_start.mp3");
	soundEffects::SNOBEE_DEATH = sound.RegisterSound(dae::SoundSystem::SoundType::sfx, "Data/Sound/snobee_death.mp3");
	soundEffects::SONG = sound.RegisterSound(dae::SoundSystem::SoundType::music, "Data/Sound/song.mp3");
	soundEffects::BUTTON_HOVER = sound.RegisterSound(dae::SoundSystem::SoundType::sfx, "Data/Sound/button_hover.wav");
	soundEffects::BUTTON_CLICK = sound.RegisterSound(dae::SoundSystem::SoundType::sfx, "Data/Sound/button_click.wav");

	dae::ServiceLocator::RegisterResourceSystem(std::make_unique<dae::SDLResourceSystem>());

	dae::SceneManager::GetInstance().SetCurrentScene(CreateMenuScene());
}

int main(int, char* [])
{
	SDL_SetMainReady();

	dae::Minigin engine("Data/");
	engine.Run(Load);
	return 0;
}
