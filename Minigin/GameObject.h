#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Transform.h"
#include "Component.h"
#include "Signal.h"

namespace dae
{
	struct SceneTreeOperationException{};

	class Texture2D;

	class GameObject final
	{
	public:
		Signal<GameObject*> MarkedForDeletion{};

		explicit GameObject(std::string&& tag = "");

		void Ready();
		void Update();
		void LateUpdate() const;
		void HandleDeletion();

		void FixedUpdate() const;
		void Render() const;
		void OnImGui() const;

		bool IsMarkedForDeletion() const { return m_MarkedForDeletion; }
		void MarkForDeletion();

		Transform& GetTransform() { return m_Transform; }


		template<std::derived_from<Component> Ty, typename... Types>
		void AddComponent(Types&&... args);

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
		std::vector<std::unique_ptr<GameObject>>& GetChildren();

		const std::string& GetTag() const { return m_Tag; }

	private:
		bool m_Ready{ false };

		Transform m_Transform{ this };
		std::vector<std::unique_ptr<Component>> m_Components{};

		GameObject* m_pParent{};
		std::vector<std::unique_ptr<GameObject>> m_Children{};

		std::string m_Tag{};

		bool m_MarkedForDeletion{ false };
	};


	template <std::derived_from<Component> Ty, typename ... Types>
	void GameObject::AddComponent(Types&&... args)
	{
		AddComponent(std::make_unique<Ty>(std::forward<Types>(args)...));
	}

	template<std::derived_from<Component> TComponent>
	TComponent* GameObject::GetComponent() const
	{
		assert(this != nullptr && "Cannot get component on null");

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
