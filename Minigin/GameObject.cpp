#include "GameObject.h"

#include "Component.h"

void dae::GameObject::Update()
{
	for (const auto& component : m_Components)
	{
		component->Update();
	}
}

void dae::GameObject::Render() const
{
	for (const auto& component : m_Components)
	{
		component->Render();
	}
}

void dae::GameObject::AddComponent(std::unique_ptr<Component> pComponent)
{
	m_Components.push_back(std::move(pComponent));
}
