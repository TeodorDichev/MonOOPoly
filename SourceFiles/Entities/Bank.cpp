#include "../../Headers/Entities/Bank.h"

Bank* Bank::instance = nullptr;

Bank* Bank::getInstance()
{
	if (!instance)
	{
		instance = new Bank();
	}

	return instance;
}

void Bank::freeInstance()
{
	delete instance;
	instance = nullptr;
}

bool Bank::hasPlayerReceivedTrade(int tradeId, int playerIndex) const
{
	for (int i = 0; i < trades.size(); i++)
	{
		if (trades[i].getReceiverIndex() == playerIndex && trades[i].getTradeId() == tradeId)
		{
			return true;
		}
	}

	return false;
}

int Bank::getTradeSenderIndex(int tradeId) const
{
	for (int i = 0; i < trades.size(); i++)
	{
		if (trades[i].getTradeId() == tradeId)
		{
			return trades[i].getSenderIndex();
		}
	}
	
	return -1;
}

int Bank::getTradeRequestedAmount(int tradeId) const
{
	for (int i = 0; i < trades.size(); i++)
	{
		if (trades[i].getTradeId() == tradeId)
		{
			return trades[i].getRequestedAmount();
		}
	}

	return -1;
}

int Bank::getPropertyIndex(int tradeId) const
{
	for (int i = 0; i < trades.size(); i++)
	{
		if (trades[i].getTradeId() == tradeId)
		{
			return trades[i].getPropertyIndex();
		}
	}

	return -1;
}

void Bank::addTrade(const Trade& trade)
{
	trades.push_back(trade);
}

void Bank::removeTradesOfPlayer(int playerId)
{
	for (int i = 0; i < trades.size(); i++)
	{
		if (trades[i].getReceiverIndex() == playerId || trades[i].getSenderIndex() == playerId)
		{
			trades.erase(i);
		}
	}
}

void Bank::printPlayerTrades(int playerIndex) const
{
	for (int i = 0; i < trades.size(); i++)
	{
		if (trades[i].getReceiverIndex() == playerIndex || trades[i].getSenderIndex() == playerIndex)
		{
			trades[i].printOffer();
		}
	}
}

void Bank::acceptTrade(int tradeId)
{
	for (int i = 0; i < trades.size(); i++)
	{
		if (trades[i].getTradeId() == tradeId)
		{
			trades[i].acceptOffer();
			std::cout << "Trade successfully accepted!" << std::endl;
			return;
		}
	}

	throw new std::invalid_argument(ExceptionMessages::invalidTradeIndex.c_str());
}
