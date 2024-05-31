#include "UIAnchor.h"

#include <glm/vec2.hpp>

#include "GameObject.h"
#include "Minigin.h"

dae::UIAnchor::UIAnchor(GameObject* pParent, UIAnchorPoint anchor)
	: Component(pParent)
	, m_Anchor{ anchor }
{
}

void dae::UIAnchor::Ready()
{
	UpdateAnchoredPosition();
}

void dae::UIAnchor::UpdateAnchoredPosition() const
{
	constexpr int w{ Minigin::WINDOW_WIDTH };
	constexpr int h{ Minigin::WINDOW_HEIGHT };

	glm::vec2 target{};
	switch (m_Anchor)
	{
	case UIAnchorPoint::topLeft:     target = { 0      , 0       }; break;
	case UIAnchorPoint::top:         target = { w / 2.f, 0       }; break;
	case UIAnchorPoint::topRight:    target = { w      , 0       }; break;
	case UIAnchorPoint::left:        target = { 0      , h / 2.f }; break;
	case UIAnchorPoint::center:      target = { w / 2.f, h / 2.f }; break;
	case UIAnchorPoint::right:       target = { w         , h / 2.f }; break;
	case UIAnchorPoint::bottomLeft:  target = { 0      , h       }; break;
	case UIAnchorPoint::bottom:      target = { w / 2.f,    h       }; break;
	case UIAnchorPoint::bottomRight: target = { w      , h       }; break;
	}

	GetParent()->GetTransform().SetLocalPosition(target);
}
