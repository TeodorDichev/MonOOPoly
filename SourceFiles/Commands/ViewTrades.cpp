#include "../../Headers/Commands/ViewTrades.h"

void ViewTrades::execute() const
{
	int playerIndex = board->getCurrentPlayerIndex();
	if (playerIndex == -1)
	{
		throw new std::invalid_argument(ExceptionMessages::notStartedGame.c_str());
	}
	if (!board->getPlayer(playerIndex))
	{
		throw new std::invalid_argument(ExceptionMessages::playerNotFound.c_str());
	}
	
	bank->printPlayerTrades(playerIndex);
}
