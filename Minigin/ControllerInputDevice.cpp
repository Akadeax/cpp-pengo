#include "ControllerInputDevice.h"

#include <map>

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#include <vector>
#include <windows.h>
#include <XInput.h>

#include "Command.h"

class dae::ControllerInputDevice::ControllerInputDeviceImpl
{
public:
	explicit ControllerInputDeviceImpl(uint32_t controllerIndex);
	void ProcessInput();

	void BindControllerButton(ControllerButton button, InputState inputState, std::unique_ptr<Command> command);

private:
	bool IsButtonDown(ControllerButton key) const;
	bool IsButtonPressed(ControllerButton key) const;
	bool IsButtonUp(ControllerButton key) const;

	using ControllerBind = std::tuple<InputState, ControllerButton, std::unique_ptr<Command>>;
	std::vector<ControllerBind> m_InputBindings{};

	XINPUT_STATE m_CurrentInput{};
	XINPUT_STATE m_LastFrameInput{};

	WORD m_ButtonsPressedThisFrame{};
	WORD m_ButtonsReleasedThisFrame{};

	uint32_t m_ControllerIndex{};
};

dae::ControllerInputDevice::ControllerInputDeviceImpl::ControllerInputDeviceImpl(uint32_t controllerIndex)
	: m_ControllerIndex{ controllerIndex }
{
	ZeroMemory(&m_CurrentInput, sizeof(XINPUT_STATE));
	ZeroMemory(&m_LastFrameInput, sizeof(XINPUT_STATE));
}

void dae::ControllerInputDevice::ControllerInputDeviceImpl::ProcessInput()
{
	CopyMemory(&m_LastFrameInput, &m_CurrentInput, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentInput, sizeof(XINPUT_STATE));
	XInputGetState(m_ControllerIndex, &m_CurrentInput);

	const auto buttonChanges{ m_CurrentInput.Gamepad.wButtons ^ m_LastFrameInput.Gamepad.wButtons };
	m_ButtonsPressedThisFrame = buttonChanges & m_CurrentInput.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges & ~m_CurrentInput.Gamepad.wButtons;

	for (const auto& [inputState, button, command] : m_InputBindings)
	{
		if (
			(inputState == InputState::down && IsButtonDown(button)) ||
			(inputState == InputState::press && IsButtonPressed(button)) ||
			(inputState == InputState::up && IsButtonUp(button))
			)
		{
			command->Execute();
		}
	}
}

void dae::ControllerInputDevice::ControllerInputDeviceImpl::BindControllerButton(ControllerButton button,
	InputState inputState, std::unique_ptr<Command> command)
{
	m_InputBindings.emplace_back(inputState, button, std::move(command));
}

bool dae::ControllerInputDevice::ControllerInputDeviceImpl::IsButtonDown(ControllerButton key) const
{
	return m_ButtonsPressedThisFrame & static_cast<int>(key);
}

bool dae::ControllerInputDevice::ControllerInputDeviceImpl::IsButtonPressed(ControllerButton key) const
{
	return m_CurrentInput.Gamepad.wButtons & static_cast<int>(key);
}

bool dae::ControllerInputDevice::ControllerInputDeviceImpl::IsButtonUp(ControllerButton key) const
{
	return m_ButtonsReleasedThisFrame & static_cast<int>(key);
}

// ============================
// ===== Pimpl forwarding =====
// ============================
dae::ControllerInputDevice::ControllerInputDevice(uint32_t controllerIndex)
	: m_pImpl{ std::make_unique<ControllerInputDeviceImpl>(controllerIndex) }
{
}

// Destructor needs to be defaulted in the cpp file
// because only here the impl type is complete (deletable)
dae::ControllerInputDevice::~ControllerInputDevice() = default;

void dae::ControllerInputDevice::ProcessInput()
{
	m_pImpl->ProcessInput();
}

void dae::ControllerInputDevice::BindControllerButton(ControllerButton button, InputState inputState, std::unique_ptr<Command> command)
{
	m_pImpl->BindControllerButton(button, inputState, std::move(command));
}
