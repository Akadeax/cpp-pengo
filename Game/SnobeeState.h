#pragma once
#include <State.h>

namespace dae
{
	class AnimatedTextureRenderer;
}

class SnobeeStateMachine;
class SnobeeController;

class SnobeeState : public dae::State
{
public:
	explicit SnobeeState(
		SnobeeController* pSnobeeController,
		SnobeeStateMachine* pStateMachine,
		dae::AnimatedTextureRenderer* pRenderer
	);

protected:
	SnobeeController* GetSnobeeController() const { return m_pSnobeeController; }
	SnobeeStateMachine* GetStateMachine() const { return m_pStateMachine; }
	dae::AnimatedTextureRenderer* GetRenderer() const { return m_pRenderer; }

private:
	SnobeeController* m_pSnobeeController;
	SnobeeStateMachine* m_pStateMachine;
	dae::AnimatedTextureRenderer* m_pRenderer;
};
