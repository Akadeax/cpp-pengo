#pragma once
#include <glm/vec2.hpp>

#include "Component.h"

namespace dae
{
	enum class UIAnchorPoint
	{
		topLeft, top, topRight, left, center, right, bottomLeft, bottom, bottomRight
	};
	class UIAnchor final : public Component
	{
	public:
		explicit UIAnchor(GameObject* pParent, UIAnchorPoint anchor, glm::vec2 offset = { 0, 0 });

		void Ready() override;
		void UpdateAnchoredPosition() const;

		glm::vec2 offset;

	private:
		UIAnchorPoint m_Anchor;
	};
}

