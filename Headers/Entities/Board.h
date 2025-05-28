#pragma once
#include "Cards/CardDeck.h"
#include "../Utills/HeterogeneousContainer.hpp"
#include "Bank.h"
#include "Trade.h"

class Board
{
private:
	int currPlayerIndex;

	Bank bank;
	CardDeck cardDeck;

	MyVector<Trade> trades;
	MyVector<Player> players;
	HeterogeneousContainer<Field*> fields;

	Board();
	static Board* instance;

public:
	static Board* getInstance();
	static void freeInstance();

	void resetPlayerIndex();
	void addPlayer(const MyString& playerName, int balance);

	void addTrade();
	void removeTrade();

	void printBoard() const;
	void nextTurn();

	void printGameSummary() const;

	friend class SerializeFunctions;
};
