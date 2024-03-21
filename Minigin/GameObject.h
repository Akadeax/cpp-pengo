#pragma once
#include <memory>
#include <vector>

#include "Transform.h"
#include "Component.h"

namespace dae
{
	struct SceneTreeOperationException{};

	class Texture2D;

	class GameObject final
	{
	public:
		GameObject() = default;

		void Ready();
		void Update() const;
		void LateUpdate() const;
		void FixedUpdate() const;
		void Render() const;
		void OnImGui() const;

		Transform& GetTransform() { return m_Transform; }

		void AddComponent(std::unique_ptr<Component> pComponent);

		void RemoveComponent(const Component* pComponent);

		template<std::derived_from<Component> TComponent>
		TComponent* GetComponent() const;

		template<std::derived_from<Component> TComponent>
		std::vector<TComponent*> GetComponents() const;

		GameObject* GetParent() const;

		void AttachChild(std::unique_ptr<GameObject> go, bool keepWorldPosition = false);
		std::unique_ptr<GameObject> DetachChild(const GameObject* go, bool keepWorldPosition = false);

		size_t GetChildCount() const;
		GameObject* GetChildAt(int index) const;
		const std::vector<std::unique_ptr<GameObject>>& GetChildren() const;

	private:
		Transform m_Transform{ this };
		std::vector<std::unique_ptr<Component>> m_Components{};

		GameObject* m_pParent{};
		std::vector<std::unique_ptr<GameObject>> m_Children{};
	};

	template<std::derived_from<Component> TComponent>
	TComponent* GameObject::GetComponent() const
	{
		for (auto& comp : m_Components)
		{
			TComponent* castComponent{ dynamic_cast<TComponent*>(comp.get()) };
			if (castComponent) return castComponent;
		}

		return nullptr;
	}

	template <std::derived_from<Component> TComponent>
	std::vector<TComponent*> GameObject::GetComponents() const
	{
		std::vector<TComponent*> matches{};

		for (auto& comp : m_Components)
		{
			TComponent* castComponent{ dynamic_cast<TComponent*>(comp.get()) };
			if (castComponent) matches.push_back(castComponent);
		}

		return matches;
	}
}
