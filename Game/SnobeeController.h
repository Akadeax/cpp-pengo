#pragma once
#include <Component.h>

#include "Signal.h"

class GridManager;
class GameManager;
class PlayerController;

class SnobeeController final : public dae::Component
{
public:
	explicit SnobeeController(dae::GameObject* pParent);

	void Ready() override;
	void Update() override;

	bool vulnerable{ false };

private:
	GridManager* m_pGridManager{};
	GameManager* m_pGameManager{};
	std::vector<PlayerController*> m_PlayerControllers{};

	static constexpr float DISTANCE_TOLERANCE2{ 24.f * 24.f };
	static constexpr int SCORE_ON_DEATH{ 500 };

	void Die() const;
};
