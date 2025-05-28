#pragma once
#include <iostream>
#include "../Entities/Board.h"
#include "../Utills/GlobalFunctionsAndConstants.h"

class Command
{
public:
	Command() = default;
	virtual void execute() const = 0;
	virtual ~Command() = default;

protected:
	Board* board;
};
