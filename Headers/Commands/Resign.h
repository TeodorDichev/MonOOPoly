#pragma once
#include "Command.h"

class Resign : public Command
{
public:
	Resign() = default;
	virtual void execute() const override;
};
