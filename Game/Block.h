#pragma once
#include <glm/vec2.hpp>

#include "Component.h"

class GridManager;

class Block final : public dae::Component
{
public:
	explicit Block(dae::GameObject* pParent);
	void Update() override;

	void Ready() override;

	void Push(glm::ivec2 dir);
	void Destroy() const;

private:
	GridManager* m_pGridManager;

	static constexpr float m_PushSpeed{ 100.f };

	bool m_IsPushing{ false };
	glm::ivec2 m_PushDir{};
};

