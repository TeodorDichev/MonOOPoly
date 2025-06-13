#include "../../Headers/Entities/Board.h"

Board::Board() : currPlayerIndex(-1)
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

bool Board::isGameOver() const
{
	return gameOver;
}

int Board::getCurrentPlayersCount() const
{
	int notResignedPlayersCount = 0;

	for (int i = 0; i < players.size(); i++)
	{
		if (!players[i].hasResigned())
		{
			notResignedPlayersCount++;
		}
	}

	return notResignedPlayersCount;
}

int Board::getCurrentPlayerIndex() const
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

	return nullptr;
}

void Board::setPlayerIndex(int value)
{
	currPlayerIndex = value;
}

void Board::addPlayer(const Player& player)
{
	players.push_back(player);
}

int Board::getBoardSize() const
{
	return fields.getSize();
}

Field* Board::getField(int index)
{
	for (int i = 0; i < fields.getSize(); i++)
	{
		if (fields[i]->getFieldIndex() == index)
		{
			return fields[i];
		}
	}

	return nullptr;
}

int Board::getJailIndex() const
{
	for (int i = 0; i < fields.getSize(); i++)
	{
		if (fields[i]->isJail())
		{
			return i;
		}
	}

	return -1;
}

void Board::playTurn()
{
	playTurn(currPlayerIndex);
}

void Board::playTurn(int playerIndex)
{
	if (getCurrentPlayersCount() == 1)
	{
		printGameSummary();
		gameOver = true;
		return;
	}

	Player* currPlayer = getPlayer(playerIndex);
	int field = currPlayer->getCurrentFieldIndex();
	currPlayerIndex = playerIndex;

	if (currPlayer->hasResigned())
	{
		playTurn(playerIndex++);
	}

	// player went to prison last turn or drew a card and should skip a turn
	if (currPlayer->shouldSkipTurn())
	{
		currPlayer->setSkipTurn(false);
		playTurn(playerIndex++);
	}

	return;
}

void Board::printGameSummary() const
{
	// TO DO
}

void Board::printBoard() const
{
	// clear the console
	std::cout << GlobalConstants::clearConsoleCode; 
	
	// prints the table
	for (int r = 0; r < GlobalConstants::tableSize; ++r) 
	{
		// Top line of current row
		for (int c = 0; c < GlobalConstants::tableSize; ++c) 
		{
			bool onBorder = (r == 0 || r == GlobalConstants::tableSize - 1 || c == 0 || c == GlobalConstants::tableSize - 1 || r == 1);
			std::cout << Field::fieldEdge(onBorder);
			
			if (r != 0 && r != 1 && r != GlobalConstants::tableSize - 1 && c == 0) 
			{
				std::cout << "+";
				std::cout << MyString::repeatChar(GlobalConstants::fieldWidth, ' ');
				c++;
			}
		}
		std::cout << "+" << std::endl;

		// Inner cell lines
		for (int h = 0; h < GlobalConstants::fieldHeight; ++h) 
		{
			for (int c = 0; c < GlobalConstants::tableSize; ++c) 
			{
				// The variable exists with the sole purpose to be know what exactly the conditions is
				bool finalColLeftLine = (c == GlobalConstants::tableSize - 1 && h == 0 && r != GlobalConstants::tableSize - 1 && r != 0);
				if (r == 0 && c == 0 || (c == 0 && h == 0) || finalColLeftLine)
				{
					std::cout << "|";
				}

				if (c == GlobalConstants::tableSize - 2 && r != 0 && r != GlobalConstants::tableSize - 1)
				{
					std::cout << MyString::repeatChar(GlobalConstants::fieldWidth, ' ');
					continue;
				}

				// Using else if to make sure edges are not printed twice
				if (r == 0) // top row including edges
				{
					int index = 20 + c;
					std::cout << fields[index]->printContent();
				}
				else if (r == GlobalConstants::tableSize - 1) // bottom row including edges
				{
					int index = 10 - c;
					std::cout << fields[index]->printContent();
				}
				else if (c == 0) 
				{
					int index = 20 - r;
					std::cout << fields[index]->printContent();
				}
				else if (c == GlobalConstants::tableSize - 1)
				{
					int index = 30 + r;
					std::cout << fields[index]->printContent();
				}
				else
				{
					std::cout << MyString::repeatChar(GlobalConstants::fieldWidth + 1, ' ');
				}
			}
			std::cout << std::endl;
		}
	}

	// Final bottom line
	for (int c = 0; c < GlobalConstants::tableSize; ++c) 
	{
		std::cout << Field::fieldEdge(true);
	}
	std::cout << "+" << std::endl;

	for (int i = 0; i < players.size(); i++)
	{
		if (currPlayerIndex == players[i].getPlayerIndex())
		{
			std::cout << "> ";
		}

		players[i].printPlayerSummary();
	}
}
