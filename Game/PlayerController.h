#pragma once
#include <Component.h>

#include "Signal.h"

class PlayerController final : public dae::Component
{
public:
	dae::Signal<> OnDeath{};
	dae::Signal<> OnGameOver{};
	dae::Signal<> OnScoreChanged{};

	explicit PlayerController(dae::GameObject* pParent);

	int GetLives() const { return m_Lives; }
	void Kill();

	int GetScore() const { return m_Score; }
	void IncreaseScore(int amount);

private:
	int m_Lives{ 3 };
	int m_Score{ 0 };
};
