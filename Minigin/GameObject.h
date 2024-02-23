#pragma once
#include <memory>
#include <vector>

#include "Transform.h"

namespace dae
{
	class Component;
	class Texture2D;

	class GameObject final
	{
	public:
		GameObject() = default;

		void Update() const;
		void LateUpdate() const;
		void FixedUpdate() const;
		void Render() const;

		Transform& GetTransform() { return m_Transform; }

		void AddComponent(std::unique_ptr<Component> pComponent);
		void RemoveComponent(const Component* pComponent);

		template<std::derived_from<Component> TComponent>
		TComponent* GetComponent() const;

		template<std::derived_from<Component> TComponent>
		std::vector<TComponent*> GetComponents() const;

	private:
		Transform m_Transform{};
		std::vector<std::unique_ptr<Component>> m_Components{};
	};


	template<std::derived_from<Component> TComponent>
	TComponent* GameObject::GetComponent() const
	{
		for (auto& comp : m_Components)
		{
			TComponent* castComponent{ dynamic_cast<TComponent*>(comp) };
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
