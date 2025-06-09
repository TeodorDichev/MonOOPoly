#include "../../Headers/Entities/Player.h"

void Player::resign()
{
	resigned = true;
	// all property and money goes to the bank
}

void Player::moveTo(Field* field)
{	
	currentFieldIndex = field->getFieldIndex();
	field->interactWithField(this);
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

void Player::buyCastle(Property* property)
{
	if (!property->hasMortgage())
	{
		throw std::invalid_argument("To buy a castle you need to have a cottage on the property!");
	}
	if (!hasSufficientFund(property->getBaseCastleValue()))
	{
		throw std::invalid_argument(ExceptionMessages::insufficientFunds.c_str());
	}

	//const Mortgage* m = property->getMortgage();
	//m->addToProperty(property); // here if mortgage is a castle will throw exception
}

void Player::buyCottage(Property* property)
{
	if (getPropertiesWithColor(property->getColor()) != 4)
	{
		throw std::invalid_argument("To buy a cottage you need to own all properties of certain color!");
	}
	if (!hasSufficientFund(property->getBaseCottageValue()))
	{
		throw std::invalid_argument(ExceptionMessages::insufficientFunds.c_str());
	}
	if (property->hasMortgage())
	{
		throw std::invalid_argument("Cannot buy a mortgage twice!");
	}

	//const Mortgage* m = property->getMortgage();
	//m->addToProperty(property);
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

	// Owner interacts with their field buys mortgage and has all properties of color
	else if (playerIndex == owner->getPlayerIndex())
	{
		MyString mortgageType;
		std::cin >> mortgageType;

		// To fix later
		if (mortgageType == "cottage")
		{
			buyCottage(field);
		}
		else if (mortgageType == "castle")
		{
			buyCastle(field);
		}
		else 
		{
			throw std::invalid_argument(ExceptionMessages::invalidMortgageName.c_str());
		}
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
