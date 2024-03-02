#include "Rotator.h"

#include "GameObject.h"
#include "Time.h"

dae::Rotator::Rotator(GameObject* pParent, float radiansPerSecond)
	: Component(pParent)
	, m_RadiansPerSecond{ radiansPerSecond }
{
}

void dae::Rotator::Update()
{
	GetParent()->GetTransform().Rotate(m_RadiansPerSecond * Time::GetInstance().GetDeltaTime());

}
