#pragma once

#include "../Utills/HeterogeneousContainer.hpp"
#include "Cards/CardDeck.h"
#include "Player.h"

class Board
{
private:
	bool gameOver = false;
	int currPlayerIndex = 0;

	CardDeck cardDeck;

	MyVector<Player> players;
	HeterogeneousContainer<Field> fields;

	Board();
	static Board* instance;

public:
	static Board* getInstance();
	static void freeInstance();

	bool isGameOver() const;
	int getCurrentPlayersCount() const;

	int getCurrentPlayerIndex() const;
	Player* getPlayer(int index);
	void addPlayer(const Player& player);

	int getBoardSize() const;
	Field* getField(int index);
	int getJailIndex() const;

	void printBoard() const;
	void playTurn(int playerIndex);
	void playTurn();

	void printGameSummary() const;
	void printWelcomeScreen() const;

	friend class SerializeFunctions;

	// These cards needs access to all players and/or getFields
	// Other solutions cause circular dependencies or needlessly 
	// overcomplicate the project
	friend class GroupPaymentCard;
	friend class MovePositionCard;
};
