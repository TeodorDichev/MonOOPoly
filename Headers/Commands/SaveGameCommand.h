#pragma once
#include "Command.h"
#include "../Utills/SerializeFunctions.h"

class SaveGameCommand : public Command
{
public:
	SaveGameCommand() = default;
	virtual void execute() const override;
};
