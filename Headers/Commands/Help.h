#pragma once
#include "Command.h"
#include "../../Headers/Utills/SerializeFunctions.h"

class Help : public Command
{
public:
	Help() = default;
	virtual void execute() const override;
};
