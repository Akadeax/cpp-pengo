#pragma once
#include <glm/vec2.hpp>

#include "Component.h"
#include "Signal.h"

class GridManager;

class Block final : public dae::Component
{
public:
	enum class Type
	{
		normal, diamond, unhatched
	};

	explicit Block(dae::GameObject* pParent);
	void Update() override;

	void Ready() override;

	void Push(glm::ivec2 dir);
	bool Destroy(bool playSound = true) const;

	Type GetType() const { return m_Type; }
	void SetType(Type type);

	bool IsMoving() const { return m_IsPushing; }

	bool pushable{ true };

private:
	GridManager* m_pGridManager{};

	static constexpr float m_PushSpeed{ 140.f };

	Type m_Type{ Type::normal };
	bool m_IsPushing{ false };
	glm::ivec2 m_PushDir{};
};

