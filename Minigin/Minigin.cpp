#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Minigin.h"

#include <chrono>
#include <iostream>
#include <thread>

#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameTime.h"

SDL_Window* g_window{};

void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
		printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
			version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

dae::Minigin::Minigin(const std::string& dataPath)
{
	PrintSDLVersion();

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init(dataPath);
}

dae::Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run(const std::function<void()>& load)
{
	load();

	auto& renderer{ Renderer::GetInstance() };
	const auto& sceneManager{ SceneManager::GetInstance() };
	auto& input{ InputManager::GetInstance() };

	sceneManager.Ready();

	constexpr float targetFPS{ 60.f };
	constexpr long targetFrameTimeMs{ static_cast<long>(1.f / targetFPS * 1000) };

	float lag{ 0.f };

	bool doContinue{ true };
	auto lastFrameStartTime{ std::chrono::high_resolution_clock::now() };

	while (doContinue)
	{
		const auto currentTime{ std::chrono::high_resolution_clock::now() };
		const float delta{ std::chrono::duration<float>(currentTime - lastFrameStartTime).count() };
		lastFrameStartTime = currentTime;

		GameTime::GetInstance().SetDeltaTime(delta);

		doContinue = input.ProcessInput();
		lag += delta;

		while (lag >= GameTime::FIXED_TIME_STEP)
		{
			sceneManager.FixedUpdate();
			lag -= GameTime::FIXED_TIME_STEP;
		}

		sceneManager.Update();
		sceneManager.LateUpdate();
		renderer.Render();

		const auto sleepAmount{ currentTime + std::chrono::milliseconds(targetFrameTimeMs) - std::chrono::high_resolution_clock::now() };
		std::this_thread::sleep_for(sleepAmount);
	}
}
