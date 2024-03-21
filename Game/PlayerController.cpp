#include "PlayerController.h"

PlayerController::PlayerController(dae::GameObject* pParent)
	: Component(pParent)
{
}

void PlayerController::Kill()
{
 	--m_Lives;
	OnDeath.Emit();

	if (m_Lives <= 0)
	{
		OnGameOver.Emit();
	}
}

void PlayerController::IncreaseScore(int amount)
{
	m_Score += amount;
	OnScoreChanged.Emit();
}
