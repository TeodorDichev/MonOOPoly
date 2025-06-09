#include "../../Headers/Entities/Board.h"

Board::Board() : currPlayerIndex(-1) // the game hasn't started yet
{ }

Board* Board::instance = nullptr;

Board* Board::getInstance()
{
	if (!instance)
	{
		instance = new Board();
	}

	return instance;
}

void Board::freeInstance()
{
	delete instance;
	instance = nullptr;
}

int Board::getWinnerIndex() const
{
	int notResignedPlayersCount = 0;
	int winnerId = -1;

	for (int i = 0; i < players.size(); i++)
	{
		if (!players[i].hasResigned())
		{
			notResignedPlayersCount++;
			winnerId = players[i].getPlayerIndex();
		}
	}

	return notResignedPlayersCount == 1 ? winnerId : -1;
}

int Board::getPlayerIndex() const
{
	return currPlayerIndex;
}

Player* Board::getPlayer(int index)
{
	for (int i = 0; i < players.size(); i++)
	{
		if(players[i].getPlayerIndex() == index)
		{
			return &players[i];
		}
	}
}

void Board::setPlayerIndex(int value)
{
	currPlayerIndex = value;
}

void Board::addPlayer(int index, const MyString& playerName, int balance)
{
	players.push_back(Player(index, playerName, balance));
}

void Board::playTurn(int playerIndex)
{
	Player* currPlayer = getPlayer(playerIndex);
	int field = currPlayer->getCurrentFieldIndex();
	currPlayerIndex = playerIndex;

	if (getWinnerIndex() != -1)
	{
		printGameSummary();
		gameOver = true;
		return;
		// end of game
	}

	if (currPlayer->hasResigned())
	{
		playTurn(playerIndex++);
	}

	// player went to prison last turn or drew a card and should skip a turn
	if (currPlayer->shouldSkipTurn())
	{
		currPlayer->resetSkipTurn();
		playTurn(playerIndex++);
	}

	if (field == getJailIndex())
	{
		std::cout << "Your are in prison either pay_prison or throw a pair to get out";
	}


	return;
}

void Board::playTurn()
{
	playTurn(currPlayerIndex);
}
