#include "../../../Headers/Entities/Fields/Property.h"

Property::Property() : Property(-1, "", "", 0, 0, 0, 0)
{ }

Property::Property(int index, const MyString& content, const MyString& color, int baseRentValue,
	int basePurchaseValue, int baseCottageValue, int baseCastleValue)
{
	this->index = index;
	this->content = content;
	this->color = color;
	this->baseRentValue = baseRentValue;
	this->basePurchaseValue = basePurchaseValue;
	this->baseCottageValue = baseCottageValue;
	this->baseCastleValue = baseCastleValue;
}

int Property::getBaseCastleValue() const
{
	return baseCastleValue;
}

int Property::getBasePurchaseValue() const
{
	return basePurchaseValue;
}

int Property::getBaseCottageValue() const
{
	return baseCottageValue;
}

Player* Property::getOwner() const
{
	return owner;
}

void Property::setOwner(Player* player)
{
	owner = player;
}

void Property::removeOwner()
{
	owner = nullptr;
}

const Mortgage* Property::getMortgage() const
{
	return mortgage;
}

void Property::addMortgage(const Mortgage& mortgage)
{
	if (this->mortgage)
	{
		delete this->mortgage;
	}

	this->mortgage = mortgage.clone();
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

void Property::printInfo() const
{
	std::cout << index << ", Property | BasePurchaseValue: " << basePurchaseValue << "$ | "
		<< "BaseCottageValue: " << baseCottageValue << "$ | "
		<< "BaseCastleValue: " << baseCastleValue << "$ | "
		<< "Rent: " << getRent() << "$ | ";

	if (owner != nullptr)
	{
		std::cout << "Owner: none" << "$ | ";
	}
	else
	{
		std::cout << "Owner: " << owner->getName() << " | ";
	}

	if (hasMortgage())
	{
		std::cout << "Mortgage: " << (mortgage->isCastle() ? "Castle" : "Cottage") << " | ";
	}

	std::cout << std::endl;
}