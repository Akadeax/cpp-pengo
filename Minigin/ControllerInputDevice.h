#pragma once
#include <map>
#include <memory>

#include "InputDevice.h"

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include <XInput.h>

#include "Command.h"


namespace dae
{
    class ControllerInputDevice final : public InputDevice // TODO pimpl xinput away
    {
    public:
        enum class ControllerButton
        {
            dpadUp = 0x0001,
            dpadDown = 0x0002,
            dpadLeft = 0x0004,
            dpadRight = 0x0008,
            start = 0x0010,
            back = 0x0020,
            leftThumb = 0x0040,
            rightThumb = 0x0080,
            leftShoulder = 0x0100,
            rightShoulder = 0x0200,
            a = 0x1000,
            b = 0x2000,
            x = 0x4000,
            y = 0x8000
        };

        explicit ControllerInputDevice(uint32_t controllerIndex);

        ~ControllerInputDevice() override = default;
        ControllerInputDevice(const ControllerInputDevice&) = delete;
        ControllerInputDevice(ControllerInputDevice&&) noexcept = delete;
        ControllerInputDevice& operator=(const ControllerInputDevice&) = delete;
        ControllerInputDevice& operator=(ControllerInputDevice&&) noexcept = delete;

        void ProcessInput() override;

        void BindControllerButton(ControllerButton button, InputState inputState, std::unique_ptr<Command> command);

    private:
        bool IsKeyDown(ControllerButton key) const;
        bool IsKeyPressed(ControllerButton key) const;
        bool IsKeyUp(ControllerButton key) const;

        using ControllerBind = std::pair<InputState, ControllerButton>;
        std::map<ControllerBind, std::unique_ptr<Command>> m_InputBindings{};

        XINPUT_STATE m_CurrentInput{};
        XINPUT_STATE m_LastFrameInput{};

        WORD m_ButtonsPressedThisFrame{};
        WORD m_ButtonsReleasedThisFrame{};

        uint32_t m_ControllerIndex{};
    };
}
