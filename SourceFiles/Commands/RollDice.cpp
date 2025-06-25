#include "../../Headers/Commands/RollDice.h"

void RollDice::execute() const
{
	int playerIndex = board->getCurrentPlayerIndex();
	if (playerIndex == -1)
	{
		throw std::invalid_argument(ExceptionMessages::noGameInProgress.c_str());
	}

	Player* currPlayer = board->getPlayer(playerIndex);
	if (!currPlayer)
	{
		throw std::invalid_argument(ExceptionMessages::playerNotFound.c_str());
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
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Press anything to continue...";
		std::cin.get();

		Field* jail = board->getField(board->getJailIndex());
		currPlayer->moveTo(jail->getFieldIndex());
		jail->interactWithField(currPlayer);

		currPlayer->resetPairsCount();
		board->playTurn(playerIndex + 1);
		return;
	}

	if (currPlayer->getCurrentFieldIndex() == board->getJailIndex() && isPair)
	{
		std::cout << "You threw a pair and you got out of prison!" << std::endl;
	}
	else if (currPlayer->getCurrentFieldIndex() == board->getJailIndex())
	{
		std::cout << "You did not throw a pair and you must pay to get out of prison! Enter 'y' if you like to pay?" << std::endl;
		MyString answer;
		std::cin >> answer;

		if (answer == "y")
		{
			currPlayer->reduceBalance(JailField::getJailTax());

			if (currPlayer->hasResigned())
			{
				board->playTurn(playerIndex + 1);
				return;
			}
		}
		else
		{
			currPlayer->resetPairsCount();
			board->playTurn(playerIndex + 1);
			return;
		}
	}

	currPlayer->moveWith(die1 + die2);
	Field* field = board->getField(currPlayer->getCurrentFieldIndex());
	field->interactWithField(currPlayer);

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Press anything to continue...";
	std::cin.get();

	if (isPair && !currPlayer->hasResigned())
	{
		std::cout << "You threw a pair so you have an additional turn!" << std::endl;
		std::cout << "Press Enter to continue...";
		std::cin.get();

		board->playTurn(playerIndex);
	}
	else
	{
		currPlayer->resetPairsCount();
		board->playTurn(playerIndex + 1);
	}
}
