#include "SnobeeStateMachine.h"

#include "GameObject.h"
#include "SnobeeChaseState.h"
#include "SnobeeStunState.h"
#include "SnobeeController.h"
#include "AnimatedTextureRenderer.h"

SnobeeStateMachine::SnobeeStateMachine(dae::GameObject* pParent)
	: StateMachine(pParent)
{
}

void SnobeeStateMachine::Ready()
{
	AddState(std::make_unique<SnobeeChaseState>(
		GetParent()->GetComponent<SnobeeController>(),
		this,
		GetParent()->GetComponent<dae::AnimatedTextureRenderer>()
	));
	m_StunStateID = AddState(std::make_unique<SnobeeStunState>(
		GetParent()->GetComponent<SnobeeController>(),
		this,
		GetParent()->GetComponent<dae::AnimatedTextureRenderer>()
	));

	SetState(0);
}

void SnobeeStateMachine::Stun()
{
	SetState(m_StunStateID);
}
