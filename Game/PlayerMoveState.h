#pragma once
#include <glm/vec2.hpp>

#include "AnimatedTextureRenderer.h"
#include "PlayerState.h"
#include "Signal.h"
#include "StateMachine.h"

class PlayerController;

class PlayerMoveState final : public PlayerState
{
public:
	PlayerMoveState(
		PlayerController* pPlayerController, 
		PlayerStateMachine* pStateMachine, 
		dae::AnimatedTextureRenderer* pRenderer, 
		dae::StateID idleStateID
	);

	void OnEnter() override;
	void Update() override;

private:
	dae::StateID m_IdleStateID;

	glm::vec2 m_MoveStartPos{};
	float m_MoveTimer{ 0.f };

	static constexpr float m_MoveTime{ 0.3f };

	dae::AnimationID m_MoveUp{};
	dae::AnimationID m_MoveRight{};
	dae::AnimationID m_MoveDown{};
	dae::AnimationID m_MoveLeft{};
};

