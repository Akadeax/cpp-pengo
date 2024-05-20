#pragma once
#include "Component.h"

class GridManager;

class Block final : public dae::Component
{
public:
	explicit Block(dae::GameObject* pParent);
	void Update() override;

	void Push(const GridManager* pGridManager);
};

