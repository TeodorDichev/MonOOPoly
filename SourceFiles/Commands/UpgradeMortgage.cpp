#include "../../Headers/Commands/UpgradeMortgage.h"

void UpgradeMortgage::execute() const
{
	int playerIndex = board->getCurrentPlayerIndex();
	if (playerIndex == -1)
	{
		throw std::invalid_argument(ExceptionMessages::notStartedGame.c_str());
	}

	Player* currPlayer = board->getPlayer(playerIndex);
	if (!currPlayer)
	{
		throw std::invalid_argument(ExceptionMessages::playerNotFound.c_str());
	}

	Property* property = currPlayer->getProperty(currPlayer->getCurrentFieldIndex());
	if (!property)
	{
		throw std::invalid_argument(ExceptionMessages::invalidFieldIndex.c_str());
	}

	MyString mortgage;
	std::cin >> mortgage;

	if (mortgage == "Cottage")
	{
		currPlayer->buyCottage(property);
	}
	else if (mortgage == "Castle")
	{
		currPlayer->buyCastle(property);
	}
	else
	{
		throw std::invalid_argument(ExceptionMessages::invalidMortgageName.c_str());
	}
}