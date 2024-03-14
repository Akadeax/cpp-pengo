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


	for (const auto& [bind, command] : m_InputBindings)
	{
		if (
			(bind.first == InputState::down && IsKeyDown(bind.second)) ||
			(bind.first == InputState::press && IsKeyPressed(bind.second)) ||
			(bind.first == InputState::up && IsKeyUp(bind.second))
			)
		{
			command->Execute();
		}
	}
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

void dae::KeyboardInputDevice::Bind(uint32_t key, InputState inputState, std::unique_ptr<Command> command)
{
	const KeyboardBind input{ inputState, static_cast<SDL_Scancode>(key) };
	m_InputBindings[input] = std::move(command);
}
