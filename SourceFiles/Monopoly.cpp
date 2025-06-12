#include "../Headers/Monopoly.h"

void Monopoly::Run()
{
	CommandFactory* factory = CommandFactory::getInstance();
	Board* board = Board::getInstance();

	while (!board->isGameOver())
	{
		MyString input;
		std::cin >> input;

		if (input == "exit")
		{
			break;
		}

		try
		{
			Command* command = factory->readCommand(input);
			command->execute();
			delete command;
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
			std::cin.clear();
		}
	}

	CommandFactory::freeInstance();
	Board::freeInstance();
	Bank::freeInstance();
}
