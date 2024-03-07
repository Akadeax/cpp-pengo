#pragma once

namespace dae
{
	class GameObject;

	class Component
	{
	public:
		virtual void Ready() {}
		virtual void Update() {}
		virtual void LateUpdate() {}
		virtual void FixedUpdate() {}
		virtual void Render() const {}
		virtual void OnImGui() {}

		explicit Component(GameObject* pParent);
		virtual ~Component() = default;

		Component(Component&& rhs) = delete;
		Component(const Component& rhs) = delete;
		Component& operator=(Component&& rhs) = delete;
		Component& operator=(const Component& rhs) = delete;

		GameObject* GetParent() const { return m_pParent; }

	private:
		GameObject* m_pParent;
	};
}

