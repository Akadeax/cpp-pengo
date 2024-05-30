#include "GridManager.h"

#include <iostream>
#include <fstream>
#include <json.hpp>
#include <random>

#include "Block.h"
#include "GameObject.h"
#include "TextureRenderer.h"

#pragma warning(push, 0)
#include <glm/gtx/string_cast.hpp>

#include "ResourceSystem.h"
#include "ServiceLocator.h"
#pragma warning(pop)

GridManager::GridManager(dae::GameObject* pParent)
	: Component(pParent)
{
}

void GridManager::Ready()
{
	std::cout << "READY\n";
	m_pBlockTexture = dae::ServiceLocator::GetResourceSystem().LoadTexture("Data/blocks.png");

	m_BlockGrid = std::vector<Block*>(GRID_WIDTH * GRID_HEIGHT);
	std::ranges::fill(m_BlockGrid, nullptr);

	SpawnLevelFromJson("Data/Levels/level1.json");

	std::vector<Block*> normalBlocks{ GetBlocksOfType(Block::Type::normal) };

	std::random_device rd;
	std::mt19937 gen{ rd() };

	std::ranges::shuffle(normalBlocks, gen);

	for(int i{}; i < DIAMOND_BLOCK_COUNT; ++i)
	{
		normalBlocks[i]->SetType(Block::Type::diamond);
	}
	for (int i{ DIAMOND_BLOCK_COUNT }; i < DIAMOND_BLOCK_COUNT + UNHATCHED_BLOCK_COUNT; ++i)
	{
		normalBlocks[i]->SetType(Block::Type::unhatched);
	}
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

glm::vec2 GridManager::LocalToGrid(glm::vec2 local) const
{
	return local * (1.f / GetBlockWorldSize());
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
	return m_BlockGrid[index];
}

void GridManager::AddBlock(glm::vec2 grid, Block* block)
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

std::vector<Block*> GridManager::GetBlocksOfType(Block::Type type)
{
	std::vector<Block*> ret{};
	std::ranges::copy_if(m_BlockGrid, std::back_inserter(ret), [type](const Block* block)
		{
			if (block == nullptr) return false;
			return block->GetType() == type;
		});

	return ret;
}

/**
 * \brief Spawn a block GameObject at the given grid position (in grid coordinates)
 */
void GridManager::SpawnBlockAt(glm::ivec2 gridPos)
{
	std::unique_ptr pBlock{ std::make_unique<dae::GameObject>() };

	// Don't apply scale when going from grid to world because this block
	// is a child of GridManager anyways, scale is applied already
	pBlock->GetTransform().SetLocalPosition(GridToWorld(gridPos, false));
	pBlock->AddComponent(std::make_unique<dae::TextureRenderer>(
		pBlock.get(),
		m_pBlockTexture,
		3, 1
	));

	std::unique_ptr<Block> pBlockComp{ std::make_unique<Block>(pBlock.get()) };

	m_BlockGrid[GridToIndex(gridPos)] = pBlockComp.get();
	pBlock->AddComponent(std::move(pBlockComp));

	GetParent()->AttachChild(std::move(pBlock), true);
}

/**
 * \brief spawn a block GameObject at the world position corresponding to `index`
 */
void GridManager::SpawnBlockAt(size_t index)
{
	SpawnBlockAt(IndexToGrid(index));
}
