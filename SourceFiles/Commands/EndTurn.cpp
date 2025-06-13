#include "../../Headers/Commands/EndTurn.h"

void EndTurn::execute() const
{
	int playerIndex = board->getCurrentPlayerIndex();
	if (playerIndex == -1)
	{
		throw std::invalid_argument(ExceptionMessages::notStartedGame.c_str());
	}
	if (!board->getPlayer(playerIndex))
	{
		throw std::invalid_argument(ExceptionMessages::playerNotFound.c_str());
	}

	board->playTurn(playerIndex++); // next player's turn
}
