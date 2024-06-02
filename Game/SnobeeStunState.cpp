#include "SnobeeStunState.h"

#include "GameTime.h"
#include "SnobeeController.h"
#include "SnobeeStateMachine.h"

SnobeeStunState::SnobeeStunState(
	SnobeeController* pSnobeeController, 
	SnobeeStateMachine* pStateMachine,
	dae::AnimatedTextureRenderer* pRenderer,
	dae::AnimationID chaseStateID
)
	: SnobeeState(pSnobeeController, pStateMachine, pRenderer)
	, m_ChaseStateID{ chaseStateID }
{
	m_Stun = GetRenderer()->AddAnimation(dae::Animation{ .5f, { 6, 7 } });
}

void SnobeeStunState::OnEnter()
{
	m_CurrentStunTime = 0.f;
	GetRenderer()->SetAnimation(m_Stun);
	GetSnobeeController()->vulnerable = true;
}

void SnobeeStunState::OnExit()
{
	GetSnobeeController()->vulnerable = false;
}

void SnobeeStunState::Update()
{
	if (m_CurrentStunTime >= STUN_TIME)
	{
		GetStateMachine()->SetState(m_ChaseStateID);
	}
	else
	{
		m_CurrentStunTime += dae::GameTime::GetInstance().GetDeltaTime();
	}
}
