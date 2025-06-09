#include "../../Headers/Commands/SellField.h"

void SellField::execute() const
{
	int fieldIndex;
	std::cin >> fieldIndex;
	
	int playerIndex = board->getPlayerIndex();
	if (playerIndex == -1)
	{
		throw new std::invalid_argument(ExceptionMessages::notStartedGame.c_str());
	}
	if (fieldIndex < 0 || fieldIndex >= GlobalFunctionsAndConstants::boardSize)
	{
		throw new std::invalid_argument(ExceptionMessages::invalidFieldIndex.c_str());
	}

	Player* currPlayer = board->getPlayer(playerIndex);

	if (!currPlayer->owsProperty(fieldIndex))
	{
		throw new std::invalid_argument(ExceptionMessages::anotherPlayerProperty.c_str());
	}

	currPlayer->sellProperty(fieldIndex);
}