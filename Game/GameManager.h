#pragma once
#include <Component.h>
#include <memory>
#include <vector>

#include "SnobeeController.h"
#include "Texture2D.h"
#include "Block.h"
#include "Timer.h"

class GameManager final : public dae::Component
{
public:
	explicit GameManager(dae::GameObject* pParent);
	void Ready() override;

	const std::vector<Block*>& GetCurrentlyMovingBlocks() const { return m_CurrentlyMovingBlocks; }

	void AdvanceLevel();

private:
	GridManager* m_pGridManager{};

	void RefillEnemiesFromUnhatched();
	void ReplaceBlockWithEnemy(const Block* block);

	void OnBlockPushStart(Block* block);
	void OnBlockPushEnd(Block* block);

	void CheckDiamondBlocks();

	void OnEnemyMarkedForDeletion(const dae::GameObject* go);

	int m_CurrentEnemyCount{};
	std::shared_ptr<dae::Texture2D> m_pSnobeeTexture{};

	std::vector<Block*> m_CurrentlyMovingBlocks{};
	dae::Timer* m_pEnemyTimer{};

	static constexpr int MAX_ENEMIES{ 3 };
	static constexpr int DIAMOND_BLOCKS_COMBINE_POINTS_WALL{ 5000 };
	static constexpr int DIAMOND_BLOCKS_COMBINE_POINTS_FREE{ 10'000 };
};
