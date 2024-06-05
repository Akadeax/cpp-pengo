#pragma once
#include "AnimatedTextureRenderer.h"
#include "SnobeeState.h"

class SnobeeStateMachine;
class GridManager;

class SnobeeChaseState final : public SnobeeState
{
public:
	explicit SnobeeChaseState(
		SnobeeController* pSnobeeController,
		SnobeeStateMachine* pStateMachine,
		dae::AnimatedTextureRenderer* pRenderer
	);

	void OnEnter() override;
	void Update() override;
	void OnExit() override;

private:
	GridManager* m_pGridManager;

	glm::vec2 m_MoveStartPos{};
	glm::vec2 m_MoveTargetPos{};
	glm::ivec2 m_MoveDir{};

	float m_TimeUntilNextMove{ 0.f };


	static constexpr float m_MoveTime{ 0.4f };

	dae::AnimationID m_ChaseUp{};
	dae::AnimationID m_ChaseRight{};
	dae::AnimationID m_ChaseDown{};
	dae::AnimationID m_ChaseLeft{};
};

