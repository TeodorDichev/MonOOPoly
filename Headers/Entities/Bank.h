#pragma once

#include "Trade.h"

class Bank
{
private:
	MyVector<Trade> trades;

	Bank() = default;
	static Bank* instance;

public:
	static Bank* getInstance();
	static void freeInstance();

	bool hasPlayerReceivedTrade(int tradeId,int playerIndex) const;

	void addTrade(const Trade& trade);
	void removeTradesOfPlayer(int playerId);
	void printPlayerTrades(int playerIndex) const;
	void acceptTrade(int tradeId);
};
