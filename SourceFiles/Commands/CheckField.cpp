#include "../../Headers/Commands/CheckField.h"

void CheckField::execute() const
{
	int playerIndex = board->getCurrentPlayerIndex();
	if (playerIndex == -1)
	{
		throw std::invalid_argument(ExceptionMessages::noGameInProgress.c_str());
	}
	if (!board->getPlayer(playerIndex))
	{
		throw std::invalid_argument(ExceptionMessages::playerNotFound.c_str());
	}

	int fieldIndex;
	std::cin >> fieldIndex;

	if (fieldIndex < 0 || fieldIndex >= board->getBoardSize())
	{
		throw std::invalid_argument(ExceptionMessages::invalidFieldIndex.c_str());
	}

	board->getField(fieldIndex)->printInfo();
}
