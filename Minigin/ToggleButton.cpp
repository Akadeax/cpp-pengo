#include "ToggleButton.h"

dae::ToggleButton::ToggleButton(GameObject* pParent, const glm::vec2& buttonClickRect, bool startOn)
	: UIButton(pParent, buttonClickRect)
	, m_On{ startOn }
{
}

void dae::ToggleButton::Ready()
{
	UIButton::Ready();

	MouseUp.Connect([this]
		{
			m_On = !m_On;
			if (m_On) ToggleOn.Emit();
			else ToggleOff.Emit();
		});
}
