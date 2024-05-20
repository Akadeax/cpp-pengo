#pragma once
#include <Command.h>
#include <glm/vec2.hpp>

class PlayerStateMachine;

class PlayerMoveCommand final : public dae::Command
{
public:
	explicit PlayerMoveCommand(dae::GameObject* pPlayer, glm::ivec2 dir);
	void Execute() override;

private:
	PlayerStateMachine* m_pPlayerStateMachine;
	glm::ivec2 m_Dir;
};
