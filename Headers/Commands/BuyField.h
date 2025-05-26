#pragma once
#include "Command.h"

class BuyField : public Command
{
public:
	BuyField() = default;
	virtual void execute() const override;
};
