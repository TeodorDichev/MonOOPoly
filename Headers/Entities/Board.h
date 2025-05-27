#pragma once
#include "Cards/CardDeck.h"
#include "../Utills/HeterogeneousContainer.hpp"
#include "Bank.h"
#include "Trade.h"

class Board
{
private:
	static Bank bank;
	static CardDeck cardDeck;

	MyVector<Trade> trades;
	MyVector<Player> players;
	HeterogeneousContainer<Field*> fields;

public:
	static int currPlayerIndex;

	void setBoard();

	void addTrade();
	void removeTrade();

	void printBoard() const;
	void nextTurn();

	void printGameSummary() const;

	friend class SerializeFunctions;
};
