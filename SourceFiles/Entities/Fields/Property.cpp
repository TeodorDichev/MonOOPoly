#include "../../../Headers/Entities/Fields/Property.h"

Property::Property() : Property(-1, "", "", 0, 0, 0, 0)
{ }

Property::Property(int index, const MyString& description, const MyString& color, int baseRentValue,
	int basePurchaseValue, int baseCottageValue, int baseCastleValue)
{
	this->index = index;
	this->description = description;
	this->color = color;
	this->baseRentValue = baseRentValue;
	this->basePurchaseValue = basePurchaseValue;
	this->baseCottageValue = baseCottageValue;
	this->baseCastleValue = baseCastleValue;
}

int Property::getBaseCastleValue() const
{
	return 0;
}

Player* Property::getOwner() const
{
	return owner;
}

void Property::setOwner(Player* player)
{
	owner = player;
}

const Mortgage* Property::getMortgage() const
{
	return mortgage;
}

void Property::addMortgage(Mortgage& mortgage)
{
	this->mortgage = &mortgage;
}

void Property::payRent() const
{
	owner->addToBalance(getRent());
}

int Property::getRent() const
{
	return hasMortgage() ? baseRentValue * mortgage->getRentIncrease() : baseRentValue;
}

bool Property::hasMortgage() const
{
	return mortgage != nullptr;
}

const MyString& Property::getColor() const
{
	return color;
}

void Property::interactWithField(Player* player)
{
	if (owner == nullptr || owner->getPlayerIndex() == player->getPlayerIndex())
	{
		return;
	}

	int rent = getRent();
	while (!player->hasSufficientFund(rent) && player->hasAnyProperties())
	{
		player->sellCheapestProperty();
	}

	if (player->hasSufficientFund(rent))
	{
		player->addToBalance(rent * (-1));
		owner->addToBalance(rent);
	}
	else
	{
		player->resign();

		std::cout << "You were unable to pay rent! You have lost!";

		owner->addToBalance(player->getBalance());
	}
}
