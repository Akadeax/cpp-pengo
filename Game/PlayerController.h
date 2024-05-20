#pragma once
#include <Component.h>
#include <glm/vec2.hpp>

#include "Signal.h"

class GridManager;

class PlayerController final : public dae::Component
{
public:
	dae::Signal<> OnDeath{};
	dae::Signal<> OnGameOver{};
	dae::Signal<> OnScoreChanged{};

	explicit PlayerController(dae::GameObject* pParent);

	void Ready() override;

	int GetLives() const { return m_Lives; }
	void Kill();

	int GetScore() const { return m_Score; }
	void IncreaseScore(int amount);

	glm::ivec2 FacingDir{};
	glm::vec2 MovementTarget{};

private:
	int m_Lives{ 3 };
	int m_Score{ 0 };
};
