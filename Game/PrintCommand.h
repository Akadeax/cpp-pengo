#pragma once
#include <Command.h>

class PrintCommand final : public dae::Command
{
public:
	void Execute() override;
};

