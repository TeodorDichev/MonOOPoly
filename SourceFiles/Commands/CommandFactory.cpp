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
	if (command == "end_turn")
	{
		return new EndTurn();
	}
	else if (command == "check_field")
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
	else if (command == "upgrade_mortgage")
	{
		return new UpgradeMortgage();
	}
	else
	{
		throw std::invalid_argument(ExceptionMessages::invalidCommand.c_str());
	}
}
