#include "../../Headers/Commands/MakeTrade.h"

void MakeTrade::execute() const
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

	int receiverIndex, fieldIndex, requestedAmount;
	MyString description;

	std::cin >> receiverIndex >> fieldIndex >> requestedAmount;
	std::cin >> description;

	Player* receiver = board->getPlayer(receiverIndex);
	if (!receiver)
	{
		throw std::invalid_argument(ExceptionMessages::playerNotFound.c_str());
	}

	Field* field = board->getField(fieldIndex);
	if (!field || !receiver->owsProperty(fieldIndex))
	{
		throw std::invalid_argument(ExceptionMessages::invalidFieldIndex.c_str());
	}

	bank->addTrade(Trade());
}
