#include "../../Headers/Commands/SellField.h"

void SellField::execute() const
{
	int playerIndex = board->getCurrentPlayerIndex();
	if (playerIndex == -1)
	{
		throw new std::invalid_argument(ExceptionMessages::notStartedGame.c_str());
	}

	Player* currPlayer = board->getPlayer(playerIndex);
	if (currPlayer)
	{
		throw new std::invalid_argument(ExceptionMessages::playerNotFound.c_str());
	}

	int fieldIndex;
	std::cin >> fieldIndex;
	if (fieldIndex < 0 || fieldIndex >= GlobalFunctionsAndConstants::boardSize)
	{
		throw new std::invalid_argument(ExceptionMessages::invalidFieldIndex.c_str());
	}
	if (!currPlayer->owsProperty(fieldIndex))
	{
		throw new std::invalid_argument(ExceptionMessages::anotherPlayerProperty.c_str());
	}

	currPlayer->sellProperty(fieldIndex);
}