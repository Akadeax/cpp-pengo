#pragma once
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
		explicit UIAnchor(GameObject* pParent, UIAnchorPoint anchor);

		void Ready() override;

		void UpdateAnchoredPosition() const;

	private:
		UIAnchorPoint m_Anchor;
	};
}

