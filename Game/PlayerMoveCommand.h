#pragma once
#include <Command.h>
#include <glm/vec2.hpp>

class PlayerController;

class PlayerMoveCommand final : public dae::Command
{
public:
	explicit PlayerMoveCommand(dae::GameObject* pPlayer, glm::vec2 dir);
	void Execute() override;

private:
	PlayerController* m_pPlayerController;
	glm::vec2 m_Dir;
};
