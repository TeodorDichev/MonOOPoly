#include "../../Headers/Entities/Player.h"

void Player::resign()
{
	resigned = true;
	// all property and money goes to the bank
}

void Player::setCurrentFieldIndex(int value)
{
	currentFieldIndex = value;
}

void Player::throwsPair()
{
	pairsCount++;
}

void Player::addToBalance(int amount)
{
	balance += amount;
}

void Player::buyProperty(Property* property)
{
	property->setOwner(this);
	addToBalance(property->getBasePurchaseValue() * (-1));
}

void Player::visit(Property* field)
{
	Player* owner = field->getOwner();

	// Property has no owner the player buys it
	if (owner == nullptr)
	{
		int purchaseValue = field->getBasePurchaseValue();

		if (hasSufficientFund(purchaseValue))
		{
			buyProperty(field);
		}

		throw std::invalid_argument(ExceptionMessages::insufficientFunds.c_str());
	}

	// Owner interacts with their field buys mortgage
	else if (playerIndex == owner->getPlayerIndex())
	{
		MyString mortgageType;
		std::cin >> mortgageType;

		// To Do
	}

	// Property is owned by another player
	else
	{
		int rent = field->getRent();
		while (!hasSufficientFund(rent) && properties.size() > 0)
		{
			sellCheapestProperty();
		}

		if (hasSufficientFund(rent))
		{
			addToBalance(rent * (-1));
			field->payRent();
		}
		else
		{
			// Player cannot pay rent and has no more properties
			resigned = true;

			std::cout << "You were unable to pay rent! You have lost!";

			owner->addToBalance(getBalance());
		}
	}
}

void Player::visit(const JailField* field)
{
	currentFieldIndex = field->getFieldIndex();
	std::cout << "You went to jail!" << std::endl;
	skipTurn = true;
}
