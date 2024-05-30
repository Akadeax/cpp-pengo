#include "Timer.h"

#include "GameTime.h"

dae::Timer::Timer(GameObject* pParent, float duration, bool startOnReady)
	: Component(pParent)
	, m_IsRunning{ startOnReady }
	, m_Duration{ duration }
{
}

void dae::Timer::Update()
{
	if (!m_IsRunning) return;

	m_CurrentDuration += GameTime::GetInstance().GetDeltaTime();

	if (m_CurrentDuration >= m_Duration)
	{
		m_IsRunning = false;
		Timeout.Emit();
	}
}

void dae::Timer::Start()
{
	m_IsRunning = true;
	m_CurrentDuration = 0.f;
}
