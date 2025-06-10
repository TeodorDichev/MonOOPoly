#pragma once
#include "Cards/CardDeck.h"
#include "../Utills/HeterogeneousContainer.hpp"

class Board
{
private:
	bool gameOver = false;
	int currPlayerIndex;

	CardDeck cardDeck;

	MyVector<Player> players;
	HeterogeneousContainer<Field> fields;

	Board();
	static Board* instance;

public:
	static Board* getInstance();
	static void freeInstance();

	bool isGameOver() const;
	int getWinnerIndex() const;

	int getCurrentPlayerIndex() const;
	Player* getPlayer(int index);

	void setPlayerIndex(int value);
	void addPlayer(int index, const MyString& playerName, int balance);

	Field* getField(int index);
	int getJailIndex() const;

	void printBoard() const;
	void playTurn(int playerIndex);
	void playTurn();

	void printGameSummary() const;

	friend class SerializeFunctions;
};
