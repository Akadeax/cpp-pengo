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
		explicit UIAnchor(GameObject* pParent, UIAnchorPoint anchor, glm::vec2 anchorPointOffset = { 0, 0 });

		void Ready() override;
		void UpdateAnchoredPosition() const;

		// user-set offset from the Anchor point
		glm::vec2 anchorPointOffset;
		// offset set by any renderers under this (for example TextAlignment)
		glm::vec2 alignmentOffset{};

	private:
		UIAnchorPoint m_Anchor;
	};
}

