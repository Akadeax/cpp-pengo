#pragma once
#include "AnimatedTextureRenderer.h"
#include "PlayerState.h"
#include "StateMachine.h"

class PlayerInteractState final : public PlayerState
{
public:
	PlayerInteractState(
		PlayerController* pPlayerController,
		PlayerStateMachine* pStateMachine,
		dae::AnimatedTextureRenderer* pRenderer,
		dae::StateID idleStateID
	);

	void OnEnter() override;
	void Update() override;

private:
	const float m_InteractionTime{ 0.3f };

	dae::StateID m_IdleStateID;

	float m_TimeSinceEnter{ 0.f };

	dae::AnimationID m_InteractUp{};
	dae::AnimationID m_InteractRight{};
	dae::AnimationID m_InteractDown{};
	dae::AnimationID m_InteractLeft{};
};

