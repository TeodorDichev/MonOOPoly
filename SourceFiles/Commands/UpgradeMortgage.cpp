#include "../../Headers/Commands/UpgradeMortgage.h"

void UpgradeMortgage::execute() const
{
	int playerIndex = board->getPlayerIndex();
	if (playerIndex == -1)
	{
		throw new std::invalid_argument(ExceptionMessages::notStartedGame.c_str());
	}

	Player* currPlayer = board->getPlayer(playerIndex);
	if (currPlayer)
	{
		throw new std::invalid_argument(ExceptionMessages::playerNotFound.c_str());
	}

	int fieldIndex = currPlayer->getCurrentFieldIndex();
	Field* field = board->getField(fieldIndex);

	if (!currPlayer->owsProperty(fieldIndex))
	{
		throw new std::invalid_argument(ExceptionMessages::cannotBuyPropertyTwice.c_str());
	}

	field->interactWithField(currPlayer);
}