#include "StateMachine.h"

#include <cassert>

#include "State.h"

dae::StateMachine::StateMachine(GameObject* pParent)
	: Component(pParent)
{
}

dae::StateID dae::StateMachine::AddState(std::unique_ptr<State> pState)
{
	m_States.push_back(std::move(pState));
	return m_States.size() - 1;
}

void dae::StateMachine::SetState(StateID id)
{
	if (id > m_States.size())
	{
		throw StateNotFoundException{};
	}

	if (m_pCurrentState) m_pCurrentState->OnExit();

	m_pCurrentState = m_States[id].get();
	m_pCurrentState->OnEnter();

}

void dae::StateMachine::Update()
{
	assert(m_pCurrentState != nullptr && "State machine has no current state. This normally happens if SetState is not called on intialization.");
	m_pCurrentState->Update();
}
