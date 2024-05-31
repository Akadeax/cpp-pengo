#pragma once
#include "SnobeeState.h"

class SnobeeStunState final : public SnobeeState
{
public:
	explicit SnobeeStunState(
		SnobeeController* pSnobeeController,
		SnobeeStateMachine* pStateMachine,
		dae::AnimatedTextureRenderer* pRenderer
	);
};

