#pragma once
#include "Command.h"
#include "../../Headers/Utills/SerializeFunctions.h"

class LoadGame : public Command
{
public:
	LoadGame() = default;
	virtual void execute() const override;
};
