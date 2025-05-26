#pragma once
#include "Command.h"

class StartNewGame : public Command
{
public:
	StartNewGame() = default;
	virtual void execute() const override;
};
