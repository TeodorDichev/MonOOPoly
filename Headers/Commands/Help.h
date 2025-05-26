#pragma once
#include "Command.h"

class Help : public Command
{
public:
	Help() = default;
	virtual void execute() const override;
};
