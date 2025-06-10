#include "../../Headers/Commands/RollDice.h"

void RollDice::execute() const
{
	int playerIndex = board->getCurrentPlayerIndex();
	if (playerIndex == -1)
	{
		throw new std::invalid_argument(ExceptionMessages::notStartedGame.c_str());
	}

	Player* currPlayer = board->getPlayer(playerIndex);
	if (currPlayer)
	{
		throw new std::invalid_argument(ExceptionMessages::playerNotFound.c_str());
	}

	std::srand(std::time(nullptr));

	int die1 = std::rand() % 6 + 1;
	int die2 = std::rand() % 6 + 1;

	std::cout << "You threw : " << die1 << ", " << die2 << std::endl;

	bool isPair = (die1 == die2);
	if (isPair)
	{
		currPlayer->throwsPair();
	}
	if (currPlayer->getPairsCount() == 3)
	{
		std::cout << "You threw a pair for third time in a roll, you are sent to jail!" << std::endl;

		Field* jail = board->getField(board->getJailIndex());
		currPlayer->moveTo(jail->getFieldIndex());
		jail->printInfo();
		jail->interactWithField(currPlayer);

		board->printBoard();

		currPlayer->resetPairsCount();
		board->playTurn(playerIndex++);
	}

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
			currPlayer->resetPairsCount();
			board->playTurn(playerIndex++);
		}
	}

	currPlayer->moveWith(die1 + die2);
	Field* field = board->getField(currPlayer->getCurrentFieldIndex());
	field->printInfo();
	field->interactWithField(currPlayer);

	board->printBoard();

	if (isPair)
	{
		std::cout << "You threw a pair so you have an additional turn!" << std::endl;
		board->playTurn(playerIndex);
	}
	else
	{
		currPlayer->resetPairsCount();
		board->playTurn(playerIndex++);
	}
}
