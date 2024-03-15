#pragma once

namespace dae
{
	class InputDevice
	{
	public:
		enum class InputState
		{
			down,
			press,
			up
		};

		InputDevice() = default;
		virtual ~InputDevice() = default;

		InputDevice(const InputDevice&) = delete;
		InputDevice(InputDevice&&) noexcept = delete;
		InputDevice& operator=(const InputDevice&) = delete;
		InputDevice& operator=(InputDevice&&) noexcept = delete;

		virtual void ProcessInput() = 0;
	};
}
