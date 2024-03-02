#pragma once
#include <glm/glm.hpp>

namespace dae
{
	class GameObject;

	class Transform final
	{
	public:
		explicit Transform(GameObject* pGameObject);
		explicit Transform(GameObject* pGameObject, glm::vec2 localPos);

		void SetDirty();

		glm::vec2 GetLocalPosition() const { return m_LocalPosition; }
		float GetLocalRotation() const { return m_LocalRotation; }
		glm::vec2 GetLocalScale() const { return m_LocalScale; }

		glm::vec2 GetWorldPosition();
		float GetWorldRotation();
		glm::vec2 GetWorldScale();

		void SetLocalPosition(glm::vec2 newLocal);
		void Translate(glm::vec2 delta);

		void SetLocalRotation(float newLocal);
		void Rotate(float delta);

		void SetLocalScale(glm::vec2 newLocal);


		void SetWorldPosition(glm::vec2 newWorld);

	private:
		GameObject* m_pGameObject;

		glm::vec2 m_LocalPosition{ 0.f, 0.f };
		float m_LocalRotation{ 0 };
		glm::vec2 m_LocalScale{ 1.f, 1.f };

		glm::vec2 m_WorldPosition{};
		float m_WorldRotation{};
		glm::vec2 m_WorldScale{};

		glm::mat4x4 m_WorldTransform{};

		bool m_Dirty{ true };

		void UpdateWorldTransform();
		glm::mat4x4 GetWorldTransform();
		void DecomposeWorldTransform();
	};
}
