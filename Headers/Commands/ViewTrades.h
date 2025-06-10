#pragma once
#include "Command.h"

class ViewTrades : public Command
{
public:
	ViewTrades() = default;
	virtual void execute() const override;
};
