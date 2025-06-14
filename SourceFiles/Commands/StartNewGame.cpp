#include "../../Headers/Commands/StartNewGame.h"

void StartNewGame::execute() const
{
	if (board->getCurrentPlayerIndex() != -1)
	{
		throw std::invalid_argument(ExceptionMessages::gameInProgress.c_str());
	}
	
	int playersCount;
	std::cin >> playersCount;

	if (playersCount < 2 || playersCount > 6)
	{
		throw std::invalid_argument(ExceptionMessages::invalidPlayersCount.c_str());
	}
	
	for (int i = 0; i < playersCount; i++)
	{
		std::cout << "Player " << i << " enter your name: ";

		MyString playerName;
		std::cin >> playerName;
		
		MyString color = GlobalConstants::colorCodeBase + MyString::fromInt(i + 1) + "m";
		board->addPlayer(Player(i, playerName, color, GlobalConstants::startingPlayerBalance));
	}

	SerializeFunctions::startNewGame();
	
	board->playTurn(0);
}
