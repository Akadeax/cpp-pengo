#pragma once
#include <memory>

#include "InputDevice.h"

namespace dae
{
	class Command;

	class ControllerInputDevice final : public InputDevice
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

        ~ControllerInputDevice() override;
        ControllerInputDevice(const ControllerInputDevice&) = delete;
        ControllerInputDevice(ControllerInputDevice&&) noexcept = delete;
        ControllerInputDevice& operator=(const ControllerInputDevice&) = delete;
        ControllerInputDevice& operator=(ControllerInputDevice&&) noexcept = delete;

        void ProcessInput() override;

        void BindControllerButton(ControllerButton button, InputState inputState, std::unique_ptr<Command> command);

    private:
        class ControllerInputDeviceImpl;
        std::unique_ptr<ControllerInputDeviceImpl> m_pImpl;
    };
}
