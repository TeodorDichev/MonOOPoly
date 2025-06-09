#include "../../Headers/Commands/ResignCommand.h"

void ResignCommand::execute() const
{
	int playerIndex = board->getPlayerIndex();
	if (playerIndex == -1)
	{
		throw new std::invalid_argument(ExceptionMessages::notStartedGame.c_str());
	}

	Player* currPlayer = board->getPlayer(playerIndex);
	currPlayer->resign();

	board->playTurn(playerIndex++);
}