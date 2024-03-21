#pragma once
#include <Command.h>
class PlayerController;

class RemoveLifeCommand final : public dae::Command
{
public:
	explicit RemoveLifeCommand(dae::GameObject* pObject);
	void Execute() override;

private:
	PlayerController* m_pPlayer;
};
