#include "../../Headers/Commands/UpgradeMortgage.h"

void UpgradeMortgage::execute() const
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

	Property* property = currPlayer->getProperty(currPlayer->getCurrentFieldIndex());
	if (!property)
	{
		throw std::invalid_argument(ExceptionMessages::anotherPlayerProperty.c_str());
	}

	MyString mortgage;
	std::cin >> mortgage;

	if (mortgage == "Cottage")
	{
		if (!currPlayer->hasAllPropertiesOfColor(property->getColor()))
		{
			throw std::invalid_argument(ExceptionMessages::invalidCottagePurchase.c_str());
		}
		if (!currPlayer->hasSufficientFund(property->getBaseCottageValue()))
		{
			throw std::invalid_argument(ExceptionMessages::insufficientFunds.c_str());
		}
		if (property->hasMortgage())
		{
			throw std::invalid_argument(ExceptionMessages::cannotBuyMortgageTwice.c_str());
		}

		currPlayer->reduceBalance(property->getBaseCottageValue());
		property->addMortgage(Cottage());
	}
	else if (mortgage == "Castle")
	{
		if (!property->hasMortgage())
		{
			throw std::invalid_argument(ExceptionMessages::invalidCastlePurchase.c_str());
		}
		if (!currPlayer->hasSufficientFund(property->getBaseCastleValue()))
		{
			throw std::invalid_argument(ExceptionMessages::insufficientFunds.c_str());
		}

		const Mortgage* m = property->getMortgage();

		if (m->isCastle())
		{
			throw std::invalid_argument(ExceptionMessages::cannotBuyMortgageTwice.c_str());
		}

		currPlayer->reduceBalance(property->getBaseCastleValue());
		property->addMortgage(Castle());
	}
	else
	{
		throw std::invalid_argument(ExceptionMessages::invalidMortgageName.c_str());
	}

	board->printBoard();
}