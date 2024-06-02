#pragma once
#include <memory>
#include <string>
#include <vector>
#include <glm/vec2.hpp>

#include "Block.h"
#include "Component.h" 
#include "Texture2D.h"

class GridManager final : public dae::Component
{
public:
	dae::Signal<Block*> BlockPushStart{};
	dae::Signal<Block*> BlockPushEnd{};

	explicit GridManager(dae::GameObject* pParent, std::string levelFilePath);
	void Ready() override;

	glm::vec2 WorldToGrid(glm::vec2 world) const;
	glm::vec2 GridToWorld(glm::vec2 grid, bool applyScale = true) const;
	glm::vec2 LocalToGrid(glm::vec2 local, bool applyScale = true) const;
	glm::vec2 GridToLocal(glm::vec2 grid, bool applyScale = true) const;
	size_t GridToIndex(glm::vec2 grid) const;
	glm::vec2 IndexToGrid(size_t index) const;

	bool HasBlock(glm::vec2 grid) const;
	Block* GetBlock(glm::vec2 grid) const;

	void AddBlock(glm::vec2 grid, Block* block);
	void RemoveBlock(glm::vec2 grid);

	void SpawnLevelFromJson(const std::string& path);

	float GetBlockWorldSize() const;
	bool IsGridPositionValid(glm::vec2 grid) const;

	std::vector<Block*> GetBlocksOfType(Block::Type type);
	std::vector<Block*>& GetBlocks() { return m_BlockGrid; }

	static constexpr int BLOCK_SQUARE_SIZE{ 16 };
	static constexpr int GRID_WIDTH{ 13 };
	static constexpr int GRID_HEIGHT{ 15 };

private:
	std::string m_LevelFilePath;

	void SpawnBlockAt(glm::ivec2 gridPos);
	void SpawnBlockAt(size_t index);

	std::vector<Block*> m_BlockGrid{};
	std::shared_ptr<dae::Texture2D> m_pBlockTexture{};

	static constexpr int DIAMOND_BLOCK_COUNT{ 3 };
	static constexpr int UNHATCHED_BLOCK_COUNT{ 6 };
};
