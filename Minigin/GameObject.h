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

		void Update();
		void Render() const;

		Transform& GetTransform() { return m_Transform; }

		void AddComponent(std::unique_ptr<Component> pComponent);

	private:
		Transform m_Transform{};
		std::vector<std::unique_ptr<Component>> m_Components{};
	};
}
