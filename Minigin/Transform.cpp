#include "Transform.h"

#include <glm/ext/matrix_transform.hpp>
#pragma warning(disable: 4201) // unnamed union is used
#include <glm/gtx/quaternion.hpp>
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
		UpdateWorldTransform();
	}

	return m_WorldPosition;
}

float dae::Transform::GetWorldRotation()
{
	if (m_Dirty)
	{
		UpdateWorldTransform();
	}

	return m_WorldRotation;
}

glm::vec2 dae::Transform::GetWorldScale()
{
	if (m_Dirty)
	{
		UpdateWorldTransform();
	}

	return m_WorldScale;
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
	SetDirty();
}

void dae::Transform::Translate(glm::vec2 delta)
{
	SetLocalPosition(m_LocalPosition + delta);
}


void dae::Transform::SetLocalRotation(float newLocal)
{
	m_LocalRotation = newLocal;
	SetDirty();
}

void dae::Transform::Rotate(float delta)
{
	m_LocalRotation += delta;
	SetDirty();
}


void dae::Transform::SetLocalScale(glm::vec2 newLocal)
{
	m_LocalScale = newLocal;
	SetDirty();
}


void dae::Transform::SetDirty()
{
	m_Dirty = true;

	for (auto& child : m_pGameObject->GetChildren())
	{
		child->GetTransform().SetDirty();
	}
}

void dae::Transform::UpdateWorldTransform()
{
	m_Dirty = false;

	glm::mat4 local{ 1 };
	local = translate(local, glm::vec3(m_LocalPosition, 0.f));
	local = rotate(local, m_LocalRotation, glm::vec3(0.f, 0.f, 1.f));
	local = scale(local, glm::vec3(m_LocalScale, 1.f));

	if (m_pGameObject->GetParent() == nullptr)
	{
		m_WorldTransform = local;
	}
	else
	{
		Transform& parentTransform{ m_pGameObject->GetParent()->GetTransform() };
		m_WorldTransform = parentTransform.GetWorldTransform() * local;
	}

	DecomposeWorldTransform();
}

glm::mat4x4 dae::Transform::GetWorldTransform()
{
	if (m_Dirty)
	{
		UpdateWorldTransform();
	}

	return m_WorldTransform;
}

void dae::Transform::DecomposeWorldTransform()
{
	// Unfortunately no math functions for 3x3 matrices, and glm::decompose is too complex for this
	// so we decompose manually
	m_WorldPosition = glm::vec2(m_WorldTransform[3][0], m_WorldTransform[3][1]);
	m_WorldRotation = eulerAngles(quat_cast(m_WorldTransform)).z;
	m_WorldScale = glm::vec2(length(m_WorldTransform[0]), length(m_WorldTransform[1]));
}

