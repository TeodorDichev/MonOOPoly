#include "../../Headers/Commands/LoadGame.h"

void LoadGame::execute() const
{
	if (board->getCurrentPlayerIndex() != -1)
	{
		throw std::invalid_argument(ExceptionMessages::gameInProgress.c_str());
	}

	SerializeFunctions::loadGameFromFile();
	board->playTurn();
}
