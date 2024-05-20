#pragma once
#include <memory>
#include <string>
#include <vector>
#include <glm/vec2.hpp>

#include "Component.h" 
#include "Texture2D.h"

class GridManager final : public dae::Component
{
public:
	explicit GridManager(dae::GameObject* pParent);
	void Ready() override;

	glm::vec2 WorldToGrid(glm::vec2 world) const;
	glm::vec2 GridToWorld(glm::vec2 grid, bool applyScale = true) const;
	size_t GridToIndex(glm::vec2 grid) const;
	glm::vec2 IndexToGrid(size_t index) const;

	bool HasBlock(glm::vec2 grid) const;

	void SpawnLevelFromJson(const std::string& path);

	float GetBlockWorldSize() const;

private:
	void SpawnBlockAt(glm::ivec2 gridPos);
	void SpawnBlockAt(size_t index);

	std::vector<dae::GameObject*> m_BlockGrid{};
	std::shared_ptr<dae::Texture2D> m_pBlockTexture{};

	static constexpr int BLOCK_SQUARE_SIZE{ 16 };
	static constexpr int GRID_WIDTH { 13 };
	static constexpr int GRID_HEIGHT{ 15 };
};
