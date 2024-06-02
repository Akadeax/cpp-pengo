#include "LivesDisplay.h"

#include <iostream>
#include <sstream>

#include "GameObject.h"
#include "PlayerController.h"
#include "TextRenderer.h"

LivesDisplay::LivesDisplay(dae::GameObject* pParent, PlayerController* pPlayerController)
	: Component(pParent)
	, m_pPlayerController{ pPlayerController }
{
}

void LivesDisplay::Ready()
{
	m_pTextRenderer = GetParent()->GetComponent<dae::TextRenderer>();
	UpdateLivesText();

	m_pPlayerController->OnDeath.Connect([this] { UpdateLivesText(); });
}

void LivesDisplay::UpdateLivesText() const
{
	std::stringstream ss{};
	ss << "Lives: " << m_pPlayerController->GetLives();
	m_pTextRenderer->SetText(ss.str());
}
