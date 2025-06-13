#include "../../Headers/Commands/ResignCommand.h"

void ResignCommand::execute() const
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

	Player* currPlayer = board->getPlayer(playerIndex);
	currPlayer->resign();
	bank->removeTradesOfPlayer(playerIndex);

	board->playTurn(playerIndex++);
}
