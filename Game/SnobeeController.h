#pragma once
#include <Component.h>

#include "Signal.h"

class GridManager;
class GameManager;

class SnobeeController final : public dae::Component
{
public:
	explicit SnobeeController(dae::GameObject* pParent);
	void Ready() override;

	void Update() override;

private:
	GridManager* m_pGridManager{};
	GameManager* m_pGameManager{};

	static constexpr float MOVING_BLOCK_DISTANCE_TOLERANCE2{ 16.f * 16.f };
};
