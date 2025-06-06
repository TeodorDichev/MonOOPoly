#pragma once
#include "Command.h"

class EndTurn : public Command
{
public:
	EndTurn() = default;
	virtual void execute() const override;
};
