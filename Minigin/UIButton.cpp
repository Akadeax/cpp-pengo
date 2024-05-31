#include "UIButton.h"

#include <iostream>

#include "GameObject.h"
#include "InputManager.h"
#include "Renderer.h"


dae::UIButton::UIButton(GameObject* pParent, glm::vec2 buttonClickRect)
	: Component(pParent)
	, m_ButtonClickSize{ buttonClickRect }
{
}

void dae::UIButton::Ready()
{
	InputManager::GetInstance().MouseDown.Connect([this](glm::vec2 pos) { CheckMouseDown(pos); });
	InputManager::GetInstance().MouseUp.Connect([this](glm::vec2 pos) { CheckMouseDown(pos); });
}

void dae::UIButton::Update()
{
	CheckHover();
}

void dae::UIButton::Render() const
{
#if _DEBUG
	const glm::vec2 localPos{ GetParent()->GetTransform().GetLocalPosition() };
	const glm::vec2 scale{ GetParent()->GetTransform().GetWorldScale() };

	Renderer::GetInstance().RenderRect(localPos, m_ButtonClickSize * scale, { 255, 0, 0, 255 });
#endif
}

void dae::UIButton::CheckHover() const
{
	std::cout << IsInBounds(InputManager::GetInstance().GetMousePosition()) << '\n';
}

void dae::UIButton::CheckMouseDown(glm::vec2) const
{

}

void dae::UIButton::CheckMouseUp(glm::vec2) const
{
}

bool dae::UIButton::IsInBounds(glm::vec2 clickPos) const
{
	const glm::vec2 localPos{ GetParent()->GetTransform().GetLocalPosition() };
	const glm::vec2 size{ m_ButtonClickSize * GetParent()->GetTransform().GetWorldScale() };


	const bool inX{ clickPos.x >= localPos.x && clickPos.x <= localPos.x + size.x };
	const bool inY{ clickPos.y >= localPos.y && clickPos.y <= localPos.y + size.y };

	return inX && inY;
}
