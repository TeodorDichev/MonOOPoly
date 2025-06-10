#include "../../Headers/Commands/AcceptTrade.h"

void AcceptTrade::execute() const
{
	int playerIndex = board->getCurrentPlayerIndex();
	if (playerIndex == -1)
	{
		throw new std::invalid_argument(ExceptionMessages::notStartedGame.c_str());
	}
	if (board->getPlayer(playerIndex))
	{
		throw new std::invalid_argument(ExceptionMessages::playerNotFound.c_str());
	}

	int tradeId;
	std::cin >> tradeId;
	
	if (!bank->hasPlayerReceivedTrade(tradeId, playerIndex))
	{
		throw new std::invalid_argument(ExceptionMessages::invalidTradeIndex.c_str());
	}

	bank->acceptTrade(tradeId);
	board->printBoard();
}
