#pragma once
#include "Command.h"

class CheckField : public Command
{
public:
	CheckField() = default;
	virtual void execute() const override;
};
