#pragma once
#include "Command.h"
#include "../Entities/Fields/JailField.h"

#include <ctime>

class RollDice : public Command
{
public:
	RollDice() = default;
	virtual void execute() const override;
};
