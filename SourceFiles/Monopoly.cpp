#include "../Headers/Monopoly.h"

void Monopoly::Run()
{
	CommandFactory* factory = CommandFactory::getInstance();

	while (true)
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
		}
	}

	CommandFactory::freeInstance();
	Board::freeInstance();
}
