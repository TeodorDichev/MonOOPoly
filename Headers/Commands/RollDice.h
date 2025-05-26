#pragma once
#include "Command.h"

class RollDice : public Command
{
public:
	RollDice() = default;
	virtual void execute() const override;
};
