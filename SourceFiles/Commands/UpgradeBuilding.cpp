#include "../../Headers/Commands/UpgradeBuilding.h"

void UpgradeBuilding::execute() const
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

	MyString building;
	std::cin >> building;

	if (building == "Cottage")
	{
		if (!currPlayer->hasAllPropertiesOfColor(property->getColor()))
		{
			throw std::invalid_argument(ExceptionMessages::invalidCottagePurchase.c_str());
		}
		if (!currPlayer->hasSufficientFund(property->getBaseCottageValue()))
		{
			throw std::invalid_argument(ExceptionMessages::insufficientFunds.c_str());
		}
		if (property->hasBuilding())
		{
			throw std::invalid_argument(ExceptionMessages::cannotBuyBuildingTwice.c_str());
		}

		currPlayer->reduceBalance(property->getBaseCottageValue());
		property->addBuilding(Cottage());
	}
	else if (building == "Castle")
	{
		if (!property->hasBuilding())
		{
			throw std::invalid_argument(ExceptionMessages::invalidCastlePurchase.c_str());
		}
		if (!currPlayer->hasSufficientFund(property->getBaseCastleValue()))
		{
			throw std::invalid_argument(ExceptionMessages::insufficientFunds.c_str());
		}

		const Building* b = property->getBuilding();

		if (b->isCastle())
		{
			throw std::invalid_argument(ExceptionMessages::cannotBuyBuildingTwice.c_str());
		}

		currPlayer->reduceBalance(property->getBaseCastleValue());
		property->addBuilding(Castle());
	}
	else
	{
		throw std::invalid_argument(ExceptionMessages::invalidBuildingName.c_str());
	}

	board->printBoard();
}
