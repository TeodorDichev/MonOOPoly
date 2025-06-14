#include "../../Headers/Commands/AcceptTrade.h"

void AcceptTrade::execute() const
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

	int tradeId;
	std::cin >> tradeId;
	
	if (!bank->hasPlayerReceivedTrade(tradeId, playerIndex))
	{
		throw std::invalid_argument(ExceptionMessages::invalidTradeIndex.c_str());
	}
	if (bank->isTradeAccepted(tradeId))
	{
		throw std::invalid_argument(ExceptionMessages::tradeAlreadyAccepted.c_str());
	}

	Player* sender = board->getPlayer(bank->getTradeSenderIndex(tradeId));
	int requestedAmount = bank->getTradeRequestedAmount(tradeId);
	int index = bank->getPropertyIndex(tradeId);

	if (sender->owsProperty(index))
	{
		// Then the sender sells the property
		Property* property = sender->getProperty(index);

		if (!currPlayer->hasSufficientFund(requestedAmount))
		{
			throw std::invalid_argument(ExceptionMessages::insufficientFunds.c_str());
		}

		property->removeOwner();
		sender->removeProperty(property->getFieldIndex());
		sender->increaseBalance(requestedAmount);

		property->setOwner(currPlayer);
		currPlayer->addProperty(property);
		currPlayer->reduceBalance(requestedAmount);
	}
	else if (currPlayer->owsProperty(index))
	{
		Property* property = currPlayer->getProperty(index);

		// Then the sender buys the property
		if (!sender->hasSufficientFund(requestedAmount))
		{
			throw std::invalid_argument(ExceptionMessages::insufficientFunds.c_str());
		}

		property->removeOwner();
		currPlayer->removeProperty(property->getFieldIndex());
		currPlayer->increaseBalance(requestedAmount);

		property->setOwner(sender);
		sender->addProperty(property);
		sender->reduceBalance(requestedAmount);
	}
	else
	{
		throw std::invalid_argument(ExceptionMessages::anotherPlayerProperty.c_str());
	}

	bank->acceptTrade(tradeId);
	board->printBoard();
}
