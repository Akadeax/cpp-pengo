#include "TextColorButton.h"

#include "GameObject.h"
#include "TextRenderer.h"

dae::TextColorButton::TextColorButton(
	GameObject* pParent,
	const glm::vec2& buttonClickRect, 
	SDL_Color normal,
	SDL_Color hover,
	SDL_Color pressed
)
	: UIButton(pParent, buttonClickRect)
	, m_NormalColor{ normal }
	, m_HoverColor{ hover }
	, m_PressedColor{ pressed }
{
}

void dae::TextColorButton::Ready()
{
	UIButton::Ready();

	m_pTextRenderer = GetParent()->GetComponent<TextRenderer>();

	m_pTextRenderer->SetColor(m_NormalColor);

	HoverStart.Connect([this]
		{
			m_pTextRenderer->SetColor(m_HoverColor);
		});
	HoverEnd.Connect([this]
		{
			m_pTextRenderer->SetColor(m_NormalColor);
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
