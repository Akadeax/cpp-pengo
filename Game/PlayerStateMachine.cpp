#include "PlayerStateMachine.h"

#include "PlayerController.h"
#include "GameObject.h"

#include "PlayerIdleState.h"
#include "PlayerInteractState.h"
#include "PlayerMoveState.h"

PlayerStateMachine::PlayerStateMachine(dae::GameObject* pParent)
	: StateMachine(pParent)
{
}

void PlayerStateMachine::Ready()
{
	AddState(std::make_unique<PlayerIdleState>(
		GetParent()->GetComponent<PlayerController>(),
		this,
		GetParent()->GetComponent<dae::AnimatedTextureRenderer>(),
		1,
		2
	));
	AddState(std::make_unique<PlayerMoveState>(
		GetParent()->GetComponent<PlayerController>(),
		this,
		GetParent()->GetComponent<dae::AnimatedTextureRenderer>(),
		0
	));
	AddState(std::make_unique<PlayerInteractState>(
		GetParent()->GetComponent<PlayerController>(),
		this,
		GetParent()->GetComponent<dae::AnimatedTextureRenderer>(),
		0
	));

	SetState(0);
}
