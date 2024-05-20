#pragma once
#include "Component.h"

class Block final : public dae::Component
{
public:
	explicit Block(dae::GameObject* pParent);
	void Update() override;
};

