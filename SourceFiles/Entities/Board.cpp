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

	if (field == getJailIndex())
	{
		Field* jail = getField(field);
		jail->interactWithField(currPlayer);
	}

	if (field >= fields.getSize()) // player has moved past starting position
	{
		currPlayer->addToBalance(200);
		currPlayer->setCurrentFieldIndex(field - fields.getSize()); // POSIBLE ERROR FOR CALCULATIONS CHECK LATER
	}
	
	return;
}

void Board::playTurn()
{
	playTurn(currPlayerIndex);
}
