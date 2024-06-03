#include "TextColorToggleButton.h"

#include "GameObject.h"
#include "TextRenderer.h"

dae::TextColorToggleButton::TextColorToggleButton(
	GameObject* pParent,
	const glm::vec2& buttonClickRect,
	bool startOn,
	SDL_Color on,
	SDL_Color off,
	SDL_Color hover,
	SDL_Color pressed
)
	: ToggleButton(pParent, buttonClickRect, startOn)
	, m_OnColor{ on }
	, m_OffColor{ off }
	, m_HoverColor{ hover }
	, m_PressedColor{ pressed }
{
}

void dae::TextColorToggleButton::Ready()
{
	ToggleButton::Ready();

	m_pTextRenderer = GetParent()->GetComponent<TextRenderer>();

	m_pTextRenderer->SetColor(m_On ? m_OnColor : m_OffColor);

	HoverStart.Connect([this]
		{
			m_pTextRenderer->SetColor(m_HoverColor);
		});
	HoverEnd.Connect([this]
		{
			m_pTextRenderer->SetColor(m_On ? m_OnColor : m_OffColor);
		});
	MouseDown.Connect([this]
		{
			m_pTextRenderer->SetColor(m_PressedColor);
		});
	MouseUp.Connect([this]
		{
			m_pTextRenderer->SetColor(m_HoverColor);
		});
}
