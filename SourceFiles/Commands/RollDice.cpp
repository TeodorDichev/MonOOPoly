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

	bool goToJail = isPair && currPlayer->getPairsCount() == 3;

	if (goToJail) 
	{
		currPlayer->setCurrentFieldIndex(board->getJailIndex());

		board->printBoard();
		std::cout << "You threw : " << die1 << ", " << die2 << std::endl;
		std::cout << "You threw a pair for third time in a roll, you are sent to jail!" << std::endl;

		board->playTurn(playerIndex++); // end of turn
	}
	else 
	{
		int newFieldIndex = currPlayer->getCurrentFieldIndex() + die1 + die2;
		currPlayer->setCurrentFieldIndex(newFieldIndex);

		board->printBoard();
		std::cout << "You threw : " << die1 << ", " << die2 << std::endl;

		Field* field = board->getField(newFieldIndex);
		field->interactWithField(currPlayer);

		if (isPair) 
		{
			std::cout << "You threw a pair so you have an additional turn!" << std::endl;
			board->playTurn(playerIndex); // additional turn
		}
		else
		{
			board->playTurn(playerIndex++); // next player's turn
		}
	}
}
