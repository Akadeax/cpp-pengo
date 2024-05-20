#include "PlayerState.h"

PlayerState::PlayerState(
	PlayerController* pPlayerController, 
	PlayerStateMachine* pStateMachine, 
	dae::AnimatedTextureRenderer* pRenderer
)
	: State()
	, m_pPlayerController{ pPlayerController }
	, m_pStateMachine{ pStateMachine }
	, m_pRenderer{ pRenderer}
{
}
