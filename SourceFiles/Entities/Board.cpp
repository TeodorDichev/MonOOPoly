#include "../../Headers/Entities/Board.h"

Board::Board() : currPlayerIndex(1)
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

void Board::resetPlayerIndex()
{
	currPlayerIndex = 1;
}

void Board::addPlayer(const MyString& playerName, int balance)
{
	players.push_back(Player(currPlayerIndex++, playerName, balance));
}
