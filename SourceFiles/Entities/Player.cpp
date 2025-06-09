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

