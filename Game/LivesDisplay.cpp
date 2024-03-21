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
	m_pTextRenderer = pParent->GetComponent<dae::TextRenderer>();
	UpdateLivesText();
}

void LivesDisplay::Ready()
{
	m_pPlayerController->OnDeath.Connect([this] { UpdateLivesText(); });
	m_pPlayerController->OnGameOver.Connect([this] { OnGameOver(); });
}

void LivesDisplay::UpdateLivesText() const
{
	std::stringstream ss{};
	ss << "# Lives: " << m_pPlayerController->GetLives();
	m_pTextRenderer->SetText(ss.str());
}

void LivesDisplay::OnGameOver() const
{
	std::cout << "That's game over :(\n";
}
