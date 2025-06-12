#include "../../Headers/Commands/LoadGame.h"

void LoadGame::execute() const
{
	SerializeFunctions::loadGameFromFile(); // will set currentPlayerIndex to the proper value 
	board->playTurn();
}
