#include "../../Headers/Commands/LoadGame.h"

void LoadGame::execute() const
{
	SerializeFunctions::loadGameFromFile();
	board->playTurn();
}
