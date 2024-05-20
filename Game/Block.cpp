#include "Block.h"

#include "GameObject.h"
#include "Transform.h"
#include "GridManager.h"

Block::Block(dae::GameObject* pParent)
	: Component(pParent)
{
}

void Block::Update()
{
}

void Block::Push(const GridManager* pGridManager)
{
	dae::Transform& blockTransform{ GetParent()->GetTransform() };
	const glm::vec2 gridPos{ pGridManager->WorldToGrid(blockTransform.GetWorldPosition()) };
	pGridManager->GetBlock(gridPos)->GetParent()->MarkForDeletion();

	// TODO: actually push here instead of useless stuff;
	// also, make sure collision gets registered properly in GridManager with the array and removing etc
}
