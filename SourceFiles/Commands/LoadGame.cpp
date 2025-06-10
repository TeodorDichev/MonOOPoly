#include "../../Headers/Commands/LoadGame.h"

void LoadGame::execute() const
{
	SerializeFunctions::loadDefaultFieldsFromFile();
	SerializeFunctions::loadGameFromFile(); // will set currentPlayerIndex to the proper value 
	board->playTurn();
}
