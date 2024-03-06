#include "Rotator.h"

#include "GameObject.h"
#include "GameTime.h"

dae::Rotator::Rotator(GameObject* pParent, float radiansPerSecond)
	: Component(pParent)
	, m_RadiansPerSecond{ radiansPerSecond }
{
}

void dae::Rotator::Update()
{
	GetParent()->GetTransform().Rotate(m_RadiansPerSecond * GameTime::GetInstance().GetDeltaTime());

}
