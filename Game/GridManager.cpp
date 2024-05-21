#include "GridManager.h"

#include <iostream>
#include <fstream>
#include <json.hpp>

#include "Block.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "TextureRenderer.h"

#pragma warning(push, 0)
#include <glm/gtx/string_cast.hpp>
#pragma warning(pop)

GridManager::GridManager(dae::GameObject* pParent)
	: Component(pParent)
{
}

void GridManager::Ready()
{
	m_pBlockTexture = dae::ResourceManager::GetInstance().LoadTexture("block.png");
	m_BlockGrid = std::vector<dae::GameObject*>(static_cast<size_t>(GRID_WIDTH * GRID_HEIGHT));
	std::ranges::fill(m_BlockGrid, nullptr);

	SpawnLevelFromJson("Data/Levels/level1.json");
}

/**
 * \brief convert from world coordinates to grid coordinates
 */
glm::vec2 GridManager::WorldToGrid(glm::vec2 world) const
{
	const glm::vec2 offsetFromGridCenter{ world - GetParent()->GetTransform().GetWorldPosition() };
	return offsetFromGridCenter * (1.f / GetBlockWorldSize());
}

/**
 * \brief convert from grid coordinates to world coordinates
 */
glm::vec2 GridManager::GridToWorld(glm::vec2 grid, bool applyScale) const
{
	const float blockSize{ applyScale ? GetBlockWorldSize() : BLOCK_SQUARE_SIZE };
	return grid * blockSize + GetParent()->GetTransform().GetLocalPosition();
}

glm::vec2 GridManager::GridToLocal(glm::vec2 grid, bool applyScale) const
{
	const float blockSize{ applyScale ? GetBlockWorldSize() : BLOCK_SQUARE_SIZE };
	return grid * blockSize;
}

/**
 * \brief convert from grid coordinates to an array index
 */
size_t GridManager::GridToIndex(glm::vec2 grid) const
{
	const glm::ivec2 toNearestGridPoint{
		lround(grid.x),
		lround(grid.y)
	};
	const int offsetX{ GRID_WIDTH / 2 };
	const int offsetY{ GRID_HEIGHT / 2 };

	const glm::ivec2 offsetNearestGridPoint{ toNearestGridPoint.x + offsetX, toNearestGridPoint.y + offsetY };
	return offsetNearestGridPoint.y * GRID_WIDTH + offsetNearestGridPoint.x;
}

/**
 * \brief convert from array index to grid coordinates
 */
glm::vec2 GridManager::IndexToGrid(size_t index) const
{
	const glm::vec2 toVec{ index % GRID_WIDTH, index / GRID_WIDTH };
	const int offsetX{ GRID_WIDTH / 2 };
	const int offsetY{ GRID_HEIGHT / 2 };

	return { toVec.x - offsetX, toVec.y - offsetY };
}

bool GridManager::HasBlock(glm::vec2 grid) const
{
	if (!IsGridPositionValid(grid)) return false;

	return m_BlockGrid[GridToIndex(grid)] != nullptr;
}

Block* GridManager::GetBlock(glm::vec2 grid) const
{
	if (!IsGridPositionValid(grid)) return nullptr;

	const size_t index{ GridToIndex(grid) };
	if (m_BlockGrid[index] == nullptr) return nullptr;
	return m_BlockGrid[index]->GetComponent<Block>();
}

void GridManager::AddBlock(glm::vec2 grid, dae::GameObject* block)
{
	m_BlockGrid[GridToIndex(grid)] = block;
}

void GridManager::RemoveBlock(glm::vec2 grid)
{
	m_BlockGrid[GridToIndex(grid)] = nullptr;
}

/**
 * \brief loads json in `path` and spawns blocks from the data in it
 * \param path json file path
 */
void GridManager::SpawnLevelFromJson(const std::string& path)
{
	const std::ifstream file(path);
	if (!file.is_open()) 
	{
		throw std::runtime_error("Could not open file: " + path);
	}

	std::stringstream buffer;
	buffer << file.rdbuf();

	const nlohmann::json json{ nlohmann::json::parse(buffer.str()) };

	for (const auto& block : json["blocks"])
	{
		const int blockIdx{ block };
		assert(blockIdx >= 0 && blockIdx < GRID_WIDTH * GRID_HEIGHT && "invalid block index, level file invalid!");
		SpawnBlockAt(blockIdx);
	}
}

float GridManager::GetBlockWorldSize() const
{
	return BLOCK_SQUARE_SIZE * GetParent()->GetTransform().GetWorldScale().x;
}

bool GridManager::IsGridPositionValid(glm::vec2 grid) const
{
	constexpr float halfWidth{ static_cast<float>(GRID_WIDTH) / 2.f };
	constexpr float halfHeight{ static_cast<float>(GRID_HEIGHT) / 2.f };
	const bool xValid{ grid.x > -halfWidth && grid.x < halfWidth };
	const bool yValid{ grid.y > -halfHeight && grid.y < halfHeight };
	return xValid && yValid;
}

/**
 * \brief Spawn a block GameObject at the given grid position (in grid coordinates)
 */
void GridManager::SpawnBlockAt(glm::ivec2 gridPos)
{
	std::unique_ptr pBlock{ std::make_unique<dae::GameObject>() };

	// Don't apply scale when going from grid to world because this block
	// is a child of GridManager anyways, so scale is applied already
	pBlock->GetTransform().SetLocalPosition(GridToWorld(gridPos, false));
	pBlock->AddComponent(std::make_unique<dae::TextureRenderer>(pBlock.get(), m_pBlockTexture));
	pBlock->AddComponent(std::make_unique<Block>(pBlock.get()));

	m_BlockGrid[GridToIndex(gridPos)] = pBlock.get();

	GetParent()->AttachChild(std::move(pBlock), true);

}

/**
 * \brief spawn a block GameObject at the world position corresponding to `index`
 */
void GridManager::SpawnBlockAt(size_t index)
{
	SpawnBlockAt(IndexToGrid(index));
}
