#pragma once
#include "Command.h"

class LoadGame : public Command
{
public:
	LoadGame() = default;
	virtual void execute() const override;
};
