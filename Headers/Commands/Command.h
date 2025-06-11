#pragma once
#include <iostream>
#include "../Entities/Board.h"
#include "../Entities/Bank.h"
#include "../Utills/GlobalFunctionsAndConstants.h"

class Command
{
public:
	Command();
	virtual void execute() const = 0;
	virtual ~Command() = default;

protected:
	Board* board;
	Bank* bank;
};
