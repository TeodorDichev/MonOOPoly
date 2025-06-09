#pragma once
#include "Command.h"

class ResignCommand : public Command
{
public:
	ResignCommand() = default;
	virtual void execute() const override;
};
