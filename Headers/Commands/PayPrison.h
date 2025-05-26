#pragma once
#include "Command.h"

class PayPrison : public Command
{
public:
	PayPrison() = default;
	virtual void execute() const override;
};
