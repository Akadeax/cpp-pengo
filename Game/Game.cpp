#define SDL_MAIN_HANDLED
#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#endif
#endif

#include <fstream>
#include <sstream>
#include "ControllerInputDevice.h"
#include "GridManager.h"
#include "SDLResourceSystem.h"
#include "SDLSoundSystem.h"
#include "ServiceLocator.h"
#include "UIButton.h"
#include "Minigin/Minigin.h"
#include "Scenes.h"
#include "json.hpp"

void Load()
{
	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::SDLSoundSystem>());
	dae::ServiceLocator::GetSoundSystem().RegisterSound(
		dae::SoundSystem::SoundType::sfx,
		"Data/Sound/act_start.mp3"
	);
	dae::ServiceLocator::RegisterResourceSystem(std::make_unique<dae::SDLResourceSystem>());

	//dae::SceneManager::GetInstance().SetCurrentScene(CreateGameScene("Data/Levels/1.json", 1));
	dae::SceneManager::GetInstance().SetCurrentScene(CreateMenuScene());
}

int main(int, char* [])
{
	SDL_SetMainReady();

	dae::Minigin engine("Data/");
	engine.Run(Load);
	return 0;
}
