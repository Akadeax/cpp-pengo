#pragma once
#include <Component.h>
#include <glm/vec2.hpp>

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

	bool IsMoving() const;
	void SetMoveDirection(glm::vec2 dir) { m_MoveDir = dir; }

	void Update() override;

private:
	float m_MoveSpeed{ 100.f };

	int m_Lives{ 3 };
	int m_Score{ 0 };

	bool m_IsMoving{ false };
	glm::vec2 m_MoveDir;
};
