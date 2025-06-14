#include "../../Headers/Commands/SaveGameCommand.h"

void SaveGameCommand::execute() const
{
	if (board->getCurrentPlayerIndex() == -1)
	{
		throw std::invalid_argument(ExceptionMessages::noGameInProgress.c_str());
	}
	
	SerializeFunctions::saveGameToFile();
	std::cout << "Game saved successfully!" << std::endl;
}