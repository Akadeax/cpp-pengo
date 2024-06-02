#include "ScoreDisplay.h"

#include <sstream>

#include "GameObject.h"
#include "PlayerController.h"
#include "TextRenderer.h"

ScoreDisplay::ScoreDisplay(dae::GameObject* pParent, PlayerController* pPlayerController)
	: Component(pParent)
	, m_pPlayerController{ pPlayerController }
{
	m_pTextRenderer = pParent->GetComponent<dae::TextRenderer>();
}

void ScoreDisplay::Ready()
{
	m_pPlayerController->OnScoreChanged.Connect([this] { UpdateScoreText(); });
	UpdateScoreText();
}

void ScoreDisplay::UpdateScoreText() const
{
	std::stringstream ss{};
	ss << "Score: " << m_pPlayerController->GetScore();
	m_pTextRenderer->SetText(ss.str());
}
