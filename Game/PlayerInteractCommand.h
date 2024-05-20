#pragma once
#include <Command.h>

class PlayerStateMachine;

class PlayerInteractCommand final : public dae::Command
{
public:
	explicit PlayerInteractCommand(dae::GameObject* pPlayer);
	void Execute() override;

private:
	PlayerStateMachine* m_pPlayerStateMachine;
};

