#include "../../../Headers/Entities/Fields/Property.h"
#include "../../../Headers/Entities/Player.h"

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

Field* Property::clone() const
{
	return new Property(*this);
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

void Property::addMortgage(const Mortgage* mortgage)
{
	if (this->mortgage)
	{
		delete this->mortgage;
	}

	this->mortgage = mortgage->clone();
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
	if (!owner)
	{
		std::cout << "Would you like to purchase this property?" << std::endl;
		MyString ans;
		std::cin >> ans;

		if (ans == "y")
		{
			player->buyProperty(this);
			this->owner = player;
		}
		else if (ans == "n")
		{
			return;
		}
		else
		{
			throw std::invalid_argument(ExceptionMessages::invalidCommand.c_str());
		}
	}
	else if (owner->getPlayerIndex() == player->getPlayerIndex())
	{
		return;
	}
	else
	{
		int rent = getRent();
		player->reduceBalance(rent);
		owner->increaseBalance(rent);
	}
}

void Property::printInfo() const
{
	std::cout << index << ", Property | BasePurchaseValue: " << basePurchaseValue << "$ | "
		<< "BaseCottageValue: " << baseCottageValue << "$ | "
		<< "BaseCastleValue: " << baseCastleValue << "$ | "
		<< "Rent: " << getRent() << "$ | ";

	if (!owner)
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

bool Property::isJail() const
{
	return false;
}

MyString Property::printContent() const
{
	if (!owner)
	{
		return content + "|";
	}

	return owner->getColorCode() + content + GlobalConstants::defaultColorCode + "|";
}

void Property::saveToBin(std::ofstream& ofs) const
{
	int type = (int)FieldType::property;
	ofs.write(reinterpret_cast<const char*>(&type), sizeof(type));

	ofs.write(reinterpret_cast<const char*>(&index), sizeof(index));
	FileFunctions::writeStringToBinFile(ofs, content);

	FileFunctions::writeStringToBinFile(ofs, color);

	ofs.write(reinterpret_cast<const char*>(&baseRentValue), sizeof(baseRentValue));
	ofs.write(reinterpret_cast<const char*>(&basePurchaseValue), sizeof(basePurchaseValue));
	ofs.write(reinterpret_cast<const char*>(&baseCottageValue), sizeof(baseCottageValue));
	ofs.write(reinterpret_cast<const char*>(&baseCastleValue), sizeof(baseCastleValue));

	int ownerIndex = 0;
	if (owner)
	{
		ownerIndex = owner->getPlayerIndex();
		ofs.write(reinterpret_cast<const char*>(&ownerIndex), sizeof(ownerIndex));
	}
	else
	{
		ofs.write(reinterpret_cast<const char*>(&ownerIndex), sizeof(ownerIndex));
	}

	int isMortgaged = mortgage != nullptr ? 1 : 0;
	ofs.write(reinterpret_cast<const char*>(&isMortgaged), sizeof(isMortgaged));

	if (isMortgaged)
	{
		mortgage->saveToBin(ofs);
	}
}
