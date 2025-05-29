#pragma once
#include "Cards/CardDeck.h"
#include "../Utills/HeterogeneousContainer.hpp"
#include "Bank.h"
#include "Trade.h"

class Board
{
private:
	int currPlayerIndex; // when loading the game to know where to start and also to check if the game has started

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

	int getPlayerIndex() const;
	Player* getPlayer(int index);

	void setPlayerIndex(int value);
	void addPlayer(int index, const MyString& playerName, int balance);

	Field* getField(int index);
	int getJailIndex() const;

	void addTrade();
	void removeTrade();

	void printBoard() const;
	void playTurn(int playerIndex);
	void playTurn();

	void printGameSummary() const;

	friend class SerializeFunctions;
};
