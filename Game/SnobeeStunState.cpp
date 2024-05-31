#include "SnobeeStunState.h"

SnobeeStunState::SnobeeStunState(
	SnobeeController* pSnobeeController, 
	SnobeeStateMachine* pStateMachine,
	dae::AnimatedTextureRenderer* pRenderer
)
	: SnobeeState(pSnobeeController, pStateMachine, pRenderer)
{
}
