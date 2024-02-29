#include "Transform.h"

#include "GameObject.h"

dae::Transform::Transform(GameObject* pGameObject)
	: Transform(pGameObject, glm::vec2(0, 0))
{
}

dae::Transform::Transform(GameObject* pGameObject, glm::vec2 localPos)
	: m_pGameObject{ pGameObject }, m_LocalPosition{ localPos }
{
}

glm::vec2 dae::Transform::GetWorldPosition()
{
	if (m_Dirty)
	{
		UpdateWorldPosition();
	}

	return m_WorldPosition;
}

void dae::Transform::SetWorldPosition(glm::vec2 newWorld)
{
	const glm::vec2 oldWorld{ GetWorldPosition() };
	const auto delta{ newWorld - oldWorld };

	SetLocalPosition(delta);
}

void dae::Transform::SetLocalPosition(glm::vec2 newLocal)
{
	m_LocalPosition = newLocal;
	SetPositionDirty();
}

void dae::Transform::Translate(glm::vec2 delta)
{
	SetLocalPosition(m_LocalPosition + delta);
}

void dae::Transform::SetPositionDirty()
{
	m_Dirty = true;

	for (auto& child : m_pGameObject->GetChildren())
	{
		child->GetTransform().SetPositionDirty();
	}
}

void dae::Transform::UpdateWorldPosition()
{
	m_Dirty = false;

	if (m_pGameObject->GetParent() == nullptr)
	{
		m_WorldPosition = m_LocalPosition;
	}
	else
	{
		Transform& transformParent{ m_pGameObject->GetParent()->GetTransform() };
		m_WorldPosition = transformParent.GetWorldPosition() + GetLocalPosition();
	}
}
