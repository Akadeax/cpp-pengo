#include "GameObject.h"

#include "Component.h"

void dae::GameObject::Update() const
{
	for (const auto& component : m_Components)
	{
		component->Update();
	}
}

void dae::GameObject::LateUpdate() const
{
	for (const auto& component : m_Components)
	{
		component->LateUpdate();
	}
}

void dae::GameObject::FixedUpdate() const
{
	for (const auto& component : m_Components)
	{
		component->FixedUpdate();
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

void dae::GameObject::RemoveComponent(const Component* pComponent)
{
	std::erase_if(m_Components, [&](const std::unique_ptr<Component>& pCurrentComp) -> bool
	{
		return pCurrentComp.get() == pComponent;
	});
}
