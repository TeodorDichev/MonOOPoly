#pragma once
#include "../Utills/MyString.h"
#include "../Utills/SerializeFunctions.h"

#include "BuyField.h"
#include "CheckField.h"
#include "Help.h"
#include "LoadGame.h"
#include "EndTurn.h"
#include "Resign.h"
#include "RollDice.h"
#include "SellField.h"
#include "StartNewGame.h"
#include "UpgradeMortgage.h"

class CommandFactory
{
public:
	static CommandFactory* getInstance();
	static void freeInstance();

	Command* readCommand(const MyString& command) const;

private:
	static CommandFactory* instance;
	CommandFactory() = default;
};