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
		void RegisterInputDevice(std::unique_ptr<InputDevice> device);

		InputDevice* GetInputDevice(size_t index) const { return m_RegisteredDevices[index].get(); }

	private:
		std::vector<std::unique_ptr<InputDevice>> m_RegisteredDevices{};
	};

}
