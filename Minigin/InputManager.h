#pragma once
#include <vector>

#include "KeyboardInputDevice.h"
#include "Singleton.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		void AddInputDevice(std::unique_ptr<InputDevice> device);

	private:
		std::vector<std::unique_ptr<InputDevice>> m_InputDevices{};
	};

}
