#include "SnobeeState.h"

SnobeeState::SnobeeState(
	SnobeeController* pSnobeeController,
	SnobeeStateMachine* pStateMachine,
	dae::AnimatedTextureRenderer* pRenderer
)
	: State()
	, m_pSnobeeController{ pSnobeeController }
	, m_pStateMachine{ pStateMachine }
	, m_pRenderer{ pRenderer }
{
}
