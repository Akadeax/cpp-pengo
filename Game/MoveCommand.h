#pragma once
#include <Command.h>
#include <glm/vec2.hpp>

class MoveCommand final : public dae::Command
{
public:
	explicit MoveCommand(dae::GameObject* pObject, glm::vec2 dir, float speed);
	void Execute() override;

private:
	glm::vec2 m_Dir;
	float m_Speed;
};

