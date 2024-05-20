#pragma once
#include <State.h>

namespace dae
{
	class AnimatedTextureRenderer;
}

class PlayerController;
class PlayerStateMachine;

class PlayerState : public dae::State
{
public:
	explicit PlayerState(
		PlayerController* pPlayerController,
		PlayerStateMachine* pStateMachine,
		dae::AnimatedTextureRenderer* pRenderer
	);

protected:
	PlayerController* GetPlayerController() const { return m_pPlayerController; }
	PlayerStateMachine* GetStateMachine() const { return m_pStateMachine; }
	dae::AnimatedTextureRenderer* GetRenderer() const { return m_pRenderer; }

private:
	PlayerController* m_pPlayerController;
	PlayerStateMachine* m_pStateMachine;
	dae::AnimatedTextureRenderer* m_pRenderer;
};

