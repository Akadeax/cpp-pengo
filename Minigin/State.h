#pragma once
#include "StateMachine.h"

namespace dae
{
	class State
	{
	public:
		explicit State(StateMachine* pStateMachine) : m_pStateMachine{ pStateMachine } {}
		
		virtual ~State() = default;

		State(const State&) = delete;
		State(State&&) noexcept = delete;
		State operator=(const State&) = delete;
		State operator=(State&&) noexcept = delete;

		virtual void OnEnter() {}
		virtual void OnExit() {}
		virtual void Update() {}

	protected:
		StateMachine* GetStateMachine() const { return m_pStateMachine; }

	private:
		StateMachine* m_pStateMachine;
	};
}
