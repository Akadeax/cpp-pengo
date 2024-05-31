#pragma once
#include <glm/vec2.hpp>

#include "Signal.h"
#include "StateMachine.h"

class PlayerStateMachine final : public dae::StateMachine
{
public:
	dae::Signal<glm::ivec2> OnMoveInput{};
	dae::Signal<> OnInteractInput{};

	explicit PlayerStateMachine(dae::GameObject* pParent);

	void Ready() override;
};
