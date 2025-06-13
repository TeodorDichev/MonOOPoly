#include "../../Headers/Commands/SaveGameCommand.h"

void SaveGameCommand::execute() const
{
	SerializeFunctions::saveGameToFile();
	std::cout << "Game saved successfully!" << std::endl;
}