#include "../../Headers/Commands/SellField.h"

void SellField::execute() const
{
	int playerIndex = board->getCurrentPlayerIndex();
	if (playerIndex == -1)
	{
		throw std::invalid_argument(ExceptionMessages::noGameInProgress.c_str());
	}

	Player* currPlayer = board->getPlayer(playerIndex);
	if (!currPlayer)
	{
		throw std::invalid_argument(ExceptionMessages::playerNotFound.c_str());
	}

	int fieldIndex;
	std::cin >> fieldIndex;
	if (fieldIndex < 0 || fieldIndex >= board->getBoardSize())
	{
		throw std::invalid_argument(ExceptionMessages::invalidFieldIndex.c_str());
	}
	if (!currPlayer->owsProperty(fieldIndex))
	{
		throw std::invalid_argument(ExceptionMessages::anotherPlayerProperty.c_str());
	}

	currPlayer->sellProperty(fieldIndex);
	board->printBoard();
}