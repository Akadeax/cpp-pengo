#pragma once
#include <array>
#include <map>
#include <memory>
#include <SDL_scancode.h>
#include <utility>

#include "Command.h"
#include "InputDevice.h"

namespace dae
{
	class KeyboardInputDevice final : public InputDevice
	{
	public:
		KeyboardInputDevice() = default;

		~KeyboardInputDevice() override = default;
		KeyboardInputDevice(const KeyboardInputDevice&) = delete;
		KeyboardInputDevice(KeyboardInputDevice&&) noexcept = delete;
		KeyboardInputDevice& operator=(const KeyboardInputDevice&) = delete;
		KeyboardInputDevice& operator=(KeyboardInputDevice&&) noexcept = delete;

		void ProcessInput() override;

		void BindKeyboardButton(SDL_Scancode key, InputState inputState, std::unique_ptr<Command> command);

	private:
		bool IsKeyDown(uint32_t key) const;
		bool IsKeyPressed(uint32_t key) const;
		bool IsKeyUp(uint32_t key) const;

		using KeyboardBind = std::pair<InputState, SDL_Scancode>;

		std::map<KeyboardBind, std::unique_ptr<Command>> m_InputBindings{};

		std::array<uint16_t, SDL_NUM_SCANCODES> m_CurrentButtons{};
		std::array<uint16_t, SDL_NUM_SCANCODES> m_LastFrameButtons{};
	};
}
