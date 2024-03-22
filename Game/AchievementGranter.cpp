#include "AchievementGranter.h"

#include <iostream>

#include "PlayerController.h"


AchievementGranter::AchievementGranter(dae::GameObject* pParent, PlayerController* pPlayer)
	: Component(pParent)
	, m_pPlayer{ pPlayer }
{
}

void AchievementGranter::Ready()
{
	m_pPlayer->OnScoreChanged.Connect([this] { CheckAchievementWinner(); });
}

void AchievementGranter::CheckAchievementWinner() const
{
	if (m_pPlayer->GetScore() >= 500)
	{
		std::cout << "ACH_WIN_ONE_GAME\n";
	}
}
