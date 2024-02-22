#include "Transform.h"

dae::Transform::Transform()
	: Transform(glm::vec2{ 0, 0 })
{
}

dae::Transform::Transform(glm::vec2 pos)
	: m_Position{ pos }
{
}

void dae::Transform::SetPosition(glm::vec2 vec)
{
	m_Position = vec;
}

void dae::Transform::SetPosition(float x, float y)
{
	m_Position.x = x;
	m_Position.y = y;
}
