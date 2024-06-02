#pragma once
#include <Command.h>
class SkipLevelCommand final : public dae::Command
{
public:
	explicit SkipLevelCommand(dae::GameObject* pGameManager);
	void Execute() override;
};

