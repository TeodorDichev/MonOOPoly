#include "../Headers/Monopoly.h"

void Monopoly::Run()
{
	CommandFactory* factory = CommandFactory::getInstance();
	Board* board = Board::getInstance();

	board->printWelcomeScreen();

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
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

	CommandFactory::freeInstance();
	Board::freeInstance();
	Bank::freeInstance();
}
