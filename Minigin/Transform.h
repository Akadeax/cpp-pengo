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

		glm::vec2 GetWorldPosition();
		glm::vec2 GetLocalPosition() const { return m_LocalPosition; }

		void SetWorldPosition(glm::vec2 newWorld);
		void SetLocalPosition(glm::vec2 newLocal);
		void Translate(glm::vec2 delta);
		void SetPositionDirty();


	private:
		GameObject* m_pGameObject;

		glm::vec2 m_LocalPosition{};
		glm::vec2 m_WorldPosition{};
		bool m_Dirty{ true };

		void UpdateWorldPosition();
	};
}
