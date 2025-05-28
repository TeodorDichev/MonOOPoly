#pragma once
#include "Command.h"
#include "../../Headers/Utills/SerializeFunctions.h"

class StartNewGame : public Command
{
public:
	StartNewGame() = default;
	virtual void execute() const override;
};
