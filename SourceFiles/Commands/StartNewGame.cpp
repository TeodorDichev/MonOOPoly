#include "../../Headers/Commands/StartNewGame.h"

void StartNewGame::execute() const
{
	int playersCount;
	std::cin >> playersCount;

	if (playersCount < 2 || playersCount > 6)
	{
		throw new std::invalid_argument("Game can have 2 to 6 players!");
	}

	SerializeFunctions::loadDefaultFieldsFromFile();
	
	for (int i = 0; i < playersCount; i++)
	{
		std::cout << "Player" << i << " enter your name: ";

		MyString playerName;
		std::cin >> playerName;
		std::cout << std::endl;

		board->addPlayer(playerName, GlobalFunctionsAndConstants::startingPlayerBalance);
	}

	board->resetPlayerIndex();
	board->nextTurn();
}