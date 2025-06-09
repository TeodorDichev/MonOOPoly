#include "../../Headers/Commands/RollDice.h"

void RollDice::execute() const
{
	int playerIndex = board->getPlayerIndex();
	if (playerIndex == -1)
	{
		throw new std::invalid_argument(ExceptionMessages::notStartedGame.c_str());
	}

	std::srand(std::time(nullptr));

	int die1 = std::rand() % 6 + 1;
	int die2 = std::rand() % 6 + 1;

	Player* currPlayer = board->getPlayer(playerIndex);
	if (currPlayer) 
	{
		throw new std::invalid_argument(ExceptionMessages::playerNotFound.c_str());
	}

	bool isPair = (die1 == die2);
	if (isPair) 
	{
		currPlayer->throwsPair();
	}

	// player did not throw a pair and must pay to get out of prison
	if (currPlayer->getCurrentFieldIndex() == board->getJailIndex() && !isPair)
	{
		std::cout << "You did not throw a pair and you must pay to get out of prison! Enter 'y' if you like to pay?" << std::endl;
		MyString answer;
		std::cin >> answer;

		if (answer == "y")
		{
			currPlayer->addToBalance(-100);
		}
		else
		{
			board->playTurn(playerIndex++);
		}
	}

	int newIndex = (currPlayer->getCurrentFieldIndex() + die1 + die2);

	if (newIndex / 39 != 0)
	{
		newIndex = newIndex % 39 - 1;
		currPlayer->addToBalance(200);
	}


	Field* field = board->getField(newIndex);
	field->interactWithField(currPlayer);

	if (currPlayer->getPairsCount() == 3)
	{
		Field* jail = board->getField(board->getJailIndex());
		currPlayer->moveTo(jail);

		board->printBoard();

		std::cout << "You threw : " << die1 << ", " << die2 << std::endl;
		std::cout << "You threw a pair for third time in a roll, you are sent to jail!" << std::endl;

		board->playTurn(playerIndex++); // end of turn
	}
	else 
	{
		currPlayer->moveTo(field);

		board->printBoard();

		std::cout << "You threw : " << die1 << ", " << die2 << std::endl;

		if (isPair) 
		{
			std::cout << "You threw a pair so you have an additional turn!" << std::endl;
			board->playTurn(playerIndex); // additional turn
		}
		else
		{
			currPlayer->resetPairsCount();
			board->playTurn(playerIndex++); // next player's turn
		}
	}
}
