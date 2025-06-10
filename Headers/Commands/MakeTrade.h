#pragma once
#include "Command.h"

class MakeTrade : public Command
{
public:
	MakeTrade() = default;
	virtual void execute() const override;
};
