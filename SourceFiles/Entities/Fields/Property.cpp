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

const Building* Property::getBuilding() const
{
	return building;
}

void Property::removeBuilding()
{
	if (this->building)
	{
		delete this->building;
	}

	this->building = nullptr;
}

void Property::addBuilding(const Building& building)
{
	if (this->building)
	{
		delete this->building;
	}

	this->building = building.clone();
}

int Property::getRent() const
{
	return hasBuilding() ? baseRentValue * building->getRentIncrease() : baseRentValue;
}

bool Property::hasBuilding() const
{
	return building != nullptr;
}

const MyString& Property::getColor() const
{
	return color;
}

void Property::interactWithField(Player* player)
{
	printInfo();

	if (owner == nullptr && player->hasSufficientFund(basePurchaseValue))
	{
		std::cout << "Press 'y' to purchase the property or anything else to continue." << std::endl;

		MyString ans;
		std::cin >> ans;

		if (ans == "y")
		{
			player->addProperty(this);
			player->reduceBalance(basePurchaseValue);
			this->owner = player;
		}
	}
	else if (owner != nullptr && owner->getPlayerIndex() != player->getPlayerIndex())
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
		std::cout << "Owner: none" << " | ";
	}
	else
	{
		std::cout << "Owner: " << owner->getName() << " | ";
	}

	if (hasBuilding())
	{
		std::cout << "Building: " << (building->isCastle() ? "Castle" : "Cottage") << " | ";
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

	int ownerIndex = -1;
	if (owner)
	{
		ownerIndex = owner->getPlayerIndex();
		ofs.write(reinterpret_cast<const char*>(&ownerIndex), sizeof(ownerIndex));
	}
	else
	{
		ofs.write(reinterpret_cast<const char*>(&ownerIndex), sizeof(ownerIndex));
	}

	bool isMortgaged = (building != nullptr ? true : false);
	ofs.write(reinterpret_cast<const char*>(&isMortgaged), sizeof(isMortgaged));

	if (isMortgaged)
	{
		building->saveToBin(ofs);
	}
}
