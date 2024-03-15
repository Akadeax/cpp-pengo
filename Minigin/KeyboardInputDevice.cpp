#include "KeyboardInputDevice.h"

#include <SDL_events.h>

void dae::KeyboardInputDevice::ProcessInput()
{
	// copies all elements over
	m_LastFrameButtons = m_CurrentButtons;

	// update the keyboard state
	SDL_PumpEvents();

	const uint8_t* pKeys{ SDL_GetKeyboardState(nullptr) };

	for (int i{}; i < SDL_NUM_SCANCODES; ++i)
	{
		m_CurrentButtons[i] = pKeys[i];
	}


	for (const auto& [inputState, key, command] : m_InputBindings)
	{
		if (
			(inputState == InputState::down && IsKeyDown(key)) ||
			(inputState == InputState::press && IsKeyPressed(key)) ||
			(inputState == InputState::up && IsKeyUp(key))
			)
		{
			command->Execute();
		}
	}
}

void dae::KeyboardInputDevice::BindKeyboardButton(SDL_Scancode key, InputState inputState, std::unique_ptr<Command> command)
{
	m_InputBindings.emplace_back(inputState, key, std::move(command));
}

bool dae::KeyboardInputDevice::IsKeyDown(uint32_t key) const
{
	return m_CurrentButtons[key] && !m_LastFrameButtons[key];
}

bool dae::KeyboardInputDevice::IsKeyPressed(uint32_t key) const
{
	return m_CurrentButtons[key];
}

bool dae::KeyboardInputDevice::IsKeyUp(uint32_t key) const
{
	return !m_CurrentButtons[key] && m_LastFrameButtons[key];
}
