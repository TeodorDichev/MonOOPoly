#pragma once
#include "Command.h"

class AcceptTrade : public Command
{
public:
	AcceptTrade() = default;
	virtual void execute() const override;
};
