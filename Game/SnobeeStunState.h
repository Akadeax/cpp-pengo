#pragma once
#include "AnimatedTextureRenderer.h"
#include "SnobeeState.h"
#include "StateMachine.h"

class SnobeeStunState final : public SnobeeState
{
public:
	explicit SnobeeStunState(
		SnobeeController* pSnobeeController,
		SnobeeStateMachine* pStateMachine,
		dae::AnimatedTextureRenderer* pRenderer,
		dae::AnimationID chaseStateID
	);

	void OnEnter() override;
	void OnExit() override;
	void Update() override;

private:
	dae::StateID m_ChaseStateID;

	float m_CurrentStunTime{ 0.f };
	static constexpr float STUN_TIME{ 10.f };

	dae::AnimationID m_Stun{};
};

