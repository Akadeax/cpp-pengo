#pragma once
#include <Command.h>
class PlayerController;

class IncreaseScoreCommand final : public dae::Command
{
public:
	explicit IncreaseScoreCommand(dae::GameObject* pObject);
	void Execute() override;

private:
	PlayerController* m_pPlayer;
};
