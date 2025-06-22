#pragma once
#include "../Utills/MyString.h"

#include "CheckField.h"
#include "Help.h"
#include "LoadGame.h"
#include "ResignCommand.h"
#include "RollDice.h"
#include "SellField.h"
#include "StartNewGame.h"
#include "UpgradeBuilding.h"
#include "MakeTrade.h"
#include "AcceptTrade.h"
#include "ViewTrades.h"
#include "SaveGameCommand.h"

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