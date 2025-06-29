#include "../../Headers/Commands/CommandFactory.h"

CommandFactory* CommandFactory::instance = nullptr;

CommandFactory* CommandFactory::getInstance()
{
	if (!instance)
	{
		instance = new CommandFactory();
	}

	return instance;
}

void CommandFactory::freeInstance()
{
	delete instance;
}

Command* CommandFactory::readCommand(const MyString& command) const
{
	if (command == "check_field")
	{
		return new CheckField();
	}
	else if (command == "help")
	{
		return new Help();
	}
	else if (command == "load_game")
	{
		return new LoadGame();
	}
	else if (command == "resign")
	{
		return new ResignCommand();
	}
	else if (command == "roll")
	{
		return new RollDice();
	}
	else if (command == "sell_field")
	{
		return new SellField();
	}
	else if (command == "start_new_game")
	{
		return new StartNewGame();
	}
	else if (command == "upgrade_building")
	{
		return new UpgradeBuilding();
	}
	else if (command == "save_game")
	{
		return new SaveGameCommand();
	}
	else if (command == "view_trades")
	{
		return new ViewTrades();
	}
	else if (command == "make_trade")
	{
		return new MakeTrade();
	}
	else if (command == "accept_trade")
	{
		return new AcceptTrade();
	}
	else
	{
		throw std::invalid_argument(ExceptionMessages::invalidCommand.c_str());
	}
}
