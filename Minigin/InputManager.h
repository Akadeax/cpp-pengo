#pragma once
#include <vector>
#include <glm/vec2.hpp>

#include "KeyboardInputDevice.h"
#include "Signal.h"
#include "Singleton.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		Signal<glm::vec2> MouseDown{};
		Signal<glm::vec2> MouseUp{};

		bool ProcessInput();
		void RegisterInputDevice(std::unique_ptr<InputDevice> device);

		InputDevice* GetInputDevice(size_t index) const { return m_RegisteredDevices[index].get(); }

		glm::vec2 GetMousePosition() const { return m_MousePosition; }

	private:
		std::vector<std::unique_ptr<InputDevice>> m_RegisteredDevices{};
		glm::vec2 m_MousePosition{};
	};

}
