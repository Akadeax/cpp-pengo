#pragma once
#include <cstdint>
#include <memory>

#include "Command.h"

namespace dae
{
	enum class InputState
	{
		down,
		press,
		up
	};

	class InputDevice
	{
	public:
		InputDevice() = default;
		virtual ~InputDevice() = default;

		InputDevice(const InputDevice&) = delete;
		InputDevice(InputDevice&&) noexcept = delete;
		InputDevice& operator=(const InputDevice&) = delete;
		InputDevice& operator=(InputDevice&&) noexcept = delete;



		virtual void ProcessInput() = 0;

		virtual bool IsKeyDown(uint32_t key) const = 0;
		virtual bool IsKeyPressed(uint32_t key) const = 0;
		virtual bool IsKeyUp(uint32_t key) const = 0;

		virtual void Bind(uint32_t key, InputState inputState, std::unique_ptr<Command> command) = 0;
	};
}
