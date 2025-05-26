#pragma once
#include "Command.h"

class SellField : public Command
{
public:
	SellField() = default;
	virtual void execute() const override;
};
