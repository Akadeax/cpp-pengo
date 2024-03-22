#pragma once
#include <Component.h>

class PlayerController;

class AchievementGranter final : public dae::Component
{
public:
	explicit AchievementGranter(dae::GameObject* pParent, PlayerController* pPlayer);

	void Ready() override;

private:
	PlayerController* m_pPlayer;

	void CheckAchievementWinner() const;
};
