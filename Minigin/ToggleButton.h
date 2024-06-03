#pragma once
#include "UIButton.h"

namespace dae
{
	class ToggleButton : public UIButton
	{
	public:
		Signal<> ToggleOn{};
		Signal<> ToggleOff{};

		ToggleButton(GameObject* pParent, const glm::vec2& buttonClickRect, bool startOn = true);

		void Ready() override;

	protected:
		bool m_On;
	};
}
