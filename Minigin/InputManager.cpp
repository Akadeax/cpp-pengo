#include <SDL.h>
#include "InputManager.h"

#include <backends/imgui_impl_sdl2.h>

bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) 
	{
		if (e.type == SDL_QUIT) 
		{
			return false;
		}

		// Passing event to ImGui
		ImGui_ImplSDL2_ProcessEvent(&e);

		if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE)
		{
			return false;
		}
	}

	for (const auto& device : m_RegisteredDevices)
	{
		device->ProcessInput();
	}
	return true;
}

void dae::InputManager::RegisterInputDevice(std::unique_ptr<InputDevice> device)
{
	m_RegisteredDevices.push_back(std::move(device));
}
