#include "../../Headers/Commands/ResignCommand.h"

void ResignCommand::execute() const
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

	currPlayer->resign();
	bank->removeTradesOfPlayer(playerIndex);

	board->playTurn(playerIndex + 1);
}
