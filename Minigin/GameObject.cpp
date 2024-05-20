#include "GameObject.h"

#include <iostream>

dae::GameObject::GameObject(std::string&& tag)
	: m_Tag{ std::move(tag) }
{
}

void dae::GameObject::Ready()
{
	for (const auto& component : m_Components)
	{
		component->Ready();
	}

	for (const auto& child : m_Children)
	{
		child->Ready();
	}
}

void dae::GameObject::Update() const
{
	for (const auto& component : m_Components)
	{
		component->Update();
	}

	for (const auto& child : m_Children)
	{
		child->Update();
	}
}

void dae::GameObject::LateUpdate() const
{
	for (const auto& component : m_Components)
	{
		component->LateUpdate();
	}

	for (const auto& child : m_Children)
	{
		child->LateUpdate();
	}
}

void dae::GameObject::HandleDeletion()
{
	std::erase_if(m_Children, [](const std::unique_ptr<GameObject>& pGo)
		{
			return pGo->IsMarkedForDeletion();
		});
}

void dae::GameObject::FixedUpdate() const
{
	for (const auto& component : m_Components)
	{
		component->FixedUpdate();
	}

	for (const auto& child : m_Children)
	{
		child->FixedUpdate();
	}
}

void dae::GameObject::Render() const
{
	for (const auto& component : m_Components)
	{
		component->Render();
	}

	for (const auto& child : m_Children)
	{
		child->Render();
	}
}

void dae::GameObject::OnImGui() const
{
	for (const auto& component : m_Components)
	{
		component->OnImGui();
	}

	for (const auto& child : m_Children)
	{
		child->OnImGui();
	}
}

void dae::GameObject::AddComponent(std::unique_ptr<Component> pComponent)
{
	m_Components.emplace_back(std::move(pComponent));
}

void dae::GameObject::RemoveComponent(const Component* pComponent)
{
	std::erase_if(m_Components, [&](const std::unique_ptr<Component>& pCurrentComp) -> bool
	{
		return pCurrentComp.get() == pComponent;
	});
}

dae::GameObject* dae::GameObject::GetParent() const
{
	return m_pParent;
}


void dae::GameObject::AttachChild(std::unique_ptr<GameObject> go, bool keepWorldPosition)
{
	if (!go) throw SceneTreeOperationException{};

	Transform& childTransform{ go->GetTransform() };
	if (keepWorldPosition)
	{
		childTransform.SetLocalPosition(childTransform.GetLocalPosition() - GetTransform().GetWorldPosition());
	}
	else
	{
		childTransform.SetLocalPosition(childTransform.GetWorldPosition());
	}

	go->m_pParent = this;
	m_Children.emplace_back(std::move(go));
}

std::unique_ptr<dae::GameObject> dae::GameObject::DetachChild(const GameObject* go, bool keepWorldPosition)
{
	const auto pos{ std::ranges::find_if(m_Children, [&](const std::unique_ptr<GameObject>& item) -> bool
	{
		return item.get() == go;
	}) };

	//go->m_Transform.SetWorldPosition(m_Transform.GetLocalPosition());
	// Move to var first so we can remove it from m_Children
	std::unique_ptr<GameObject> detached{ std::move(*pos) };

	detached->m_pParent = nullptr;

	Transform& detachedTransform{ detached->GetTransform() };
	if (keepWorldPosition)
	{
		detachedTransform.SetLocalPosition(GetTransform().GetWorldPosition() + detachedTransform.GetLocalPosition());
	}
	detached->GetTransform().SetDirty();

	m_Children.erase(std::begin(m_Children));

	return std::move(detached);
}

size_t dae::GameObject::GetChildCount() const
{
	return m_Children.size();
}

dae::GameObject* dae::GameObject::GetChildAt(int index) const
{
	return m_Children[index].get();
}

const std::vector<std::unique_ptr<dae::GameObject>>& dae::GameObject::GetChildren() const
{
	return m_Children;
}
