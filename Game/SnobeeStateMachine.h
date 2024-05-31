#pragma once
#include "StateMachine.h"

class SnobeeStateMachine final : public dae::StateMachine
{
public:
	explicit SnobeeStateMachine(dae::GameObject* pParent);
	void Ready() override;

	void Stun();

private:
	dae::StateID m_StunStateID{};
};
