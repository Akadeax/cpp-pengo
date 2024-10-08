#pragma once
#include <memory>
#include <vector>

#include "Component.h"
#include "State.h"

namespace dae
{
	class StateNotFoundException{};
	using StateID = size_t;

	class StateMachine : public Component
	{
	public:
		explicit StateMachine(GameObject* pParent);

		StateID AddState(std::unique_ptr<State> pState);
		void SetState(StateID id);

		void Update() override;

	private:
		std::vector<std::unique_ptr<State>> m_States{};
		State* m_pCurrentState{};
	};
}
