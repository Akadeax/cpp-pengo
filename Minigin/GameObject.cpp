#include "GameObject.h"

#include <iostream>

dae::GameObject::GameObject(std::string&& tag)
	: m_Tag{ std::move(tag) }
{
}

void dae::GameObject::Ready()
{
	m_Ready = true;

	for (size_t i{}; i < m_Components.size(); ++i)
	{
		m_Components[i]->Ready();
	}

	for (size_t i{}; i < m_Children.size(); ++i)
	{
		m_Children[i]->Ready();
	}
}

void dae::GameObject::Update()
{
	if (!m_Ready)
	{
		Ready();
	}

	for (size_t i{}; i < m_Components.size(); ++i)
	{
		m_Components[i]->Update();
	}

	for (size_t i{}; i < m_Children.size(); ++i)
	{
		m_Children[i]->Update();
	}
}

void dae::GameObject::LateUpdate() const
{
	for (size_t i{}; i < m_Components.size(); ++i)
	{
		m_Components[i]->LateUpdate();
	}

	for (size_t i{}; i < m_Children.size(); ++i)
	{
		m_Children[i]->LateUpdate();
	}
}

void dae::GameObject::HandleDeletion()
{
	std::erase_if(m_Children, [](const std::unique_ptr<GameObject>& pGo)
		{
			return pGo->IsMarkedForDeletion();
		});

	for (size_t i{}; i < m_Children.size(); ++i)
	{
		m_Children[i]->HandleDeletion();
	}
}

void dae::GameObject::FixedUpdate() const
{
	for (size_t i{}; i < m_Components.size(); ++i)
	{
		m_Components[i]->FixedUpdate();
	}

	for (size_t i{}; i < m_Children.size(); ++i)
	{
		m_Children[i]->FixedUpdate();
	}
}

void dae::GameObject::Render() const
{
	for (size_t i{}; i < m_Components.size(); ++i)
	{
		m_Components[i]->Render();
	}

	for (size_t i{}; i < m_Children.size(); ++i)
	{
		m_Children[i]->Render();
	}
}

void dae::GameObject::OnImGui() const
{
	for (size_t i{}; i < m_Components.size(); ++i)
	{
		m_Components[i]->OnImGui();
	}

	for (size_t i{}; i < m_Children.size(); ++i)
	{
		m_Children[i]->OnImGui();
	}
}

void dae::GameObject::MarkForDeletion()
{
	m_MarkedForDeletion = true;
	MarkedForDeletion.Emit(this);
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

std::vector<std::unique_ptr<dae::GameObject>>& dae::GameObject::GetChildren()
{
	return m_Children;
}
