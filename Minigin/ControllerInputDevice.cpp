#include "ControllerInputDevice.h"

#include <Xinput.h>

dae::ControllerInputDevice::ControllerInputDevice(uint32_t controllerIndex)
	: m_ControllerIndex{ controllerIndex }
{
	ZeroMemory(&m_CurrentInput, sizeof(XINPUT_STATE));
	ZeroMemory(&m_LastFrameInput, sizeof(XINPUT_STATE));
}

void dae::ControllerInputDevice::ProcessInput()
{
	CopyMemory(&m_LastFrameInput, &m_CurrentInput, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentInput, sizeof(XINPUT_STATE));
	XInputGetState(m_ControllerIndex, &m_CurrentInput);

	const auto buttonChanges{ m_CurrentInput.Gamepad.wButtons ^ m_LastFrameInput.Gamepad.wButtons };
	m_ButtonsPressedThisFrame = buttonChanges & m_CurrentInput.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges & ~m_CurrentInput.Gamepad.wButtons;

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

void dae::ControllerInputDevice::BindControllerButton(ControllerButton button, InputState inputState, std::unique_ptr<Command> command)
{
	const ControllerBind input{ inputState, button };
	m_InputBindings[input] = std::move(command);
}

bool dae::ControllerInputDevice::IsKeyDown(ControllerButton key) const
{
	return m_ButtonsPressedThisFrame & static_cast<int>(key);
}

bool dae::ControllerInputDevice::IsKeyPressed(ControllerButton key) const
{
	return m_CurrentInput.Gamepad.wButtons & static_cast<int>(key);
}

bool dae::ControllerInputDevice::IsKeyUp(ControllerButton key) const
{
	return m_ButtonsReleasedThisFrame & static_cast<int>(key);
}
