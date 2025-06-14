#include "../../Headers/Commands/MakeTrade.h"

void MakeTrade::execute() const
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

	int receiverIndex, fieldIndex, requestedAmount;
	MyString description;

	std::cin >> receiverIndex >> fieldIndex >> requestedAmount;
	std::cin >> description;

	Player* receiver = board->getPlayer(receiverIndex);
	if (!receiver || receiver == currPlayer)
	{
		throw std::invalid_argument(ExceptionMessages::playerNotFound.c_str());
	}

	if (!currPlayer->owsProperty(fieldIndex) && !receiver->owsProperty(fieldIndex))
	{
		throw std::invalid_argument(ExceptionMessages::invalidFieldIndex.c_str());
	}

	bank->addTrade(Trade(currPlayer, receiver, description, fieldIndex, requestedAmount));
}
