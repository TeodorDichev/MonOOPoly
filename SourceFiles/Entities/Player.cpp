#include "../../Headers/Entities/Player.h"

Player::Player() : Player(-1, "", 0)
{ }

Player::Player(int playerIndex, const MyString& playerName, int playerBalance) : playerIndex(playerIndex), playerName(playerName), balance(playerBalance)
{ }

Player::Player(int playerIndex, const MyString& playerName, int playerBalance, bool resigned, bool skipTurn, int pairsCount, int currentFieldIndex) 
	: Player(playerIndex, playerName, playerBalance)
{
	this->resigned = resigned;
	this->skipTurn = skipTurn;
	this->pairsCount = pairsCount;
	this->currentFieldIndex = currentFieldIndex;
}

void Player::resign()
{
	resigned = true;
	
	playerIndex = -1;
	currentFieldIndex = -1;

	for (int i = 0; i < properties.size(); i++)
	{
		properties[i].removeOwner();
	}
}

void Player::moveWith(int positions)
{	
	int newIndex = currentFieldIndex + positions;

	if (newIndex / 39 != 0)
	{
		newIndex = newIndex % 39 - 1;
		increaseBalance(200);
	}

	currentFieldIndex = newIndex;
}

void Player::moveTo(int index)
{
	currentFieldIndex = index;
}

void Player::increaseBalance(int amount)
{
	balance += amount;
}

void Player::reduceBalance(int amount)
{
	while (!hasSufficientFund(amount) && hasAnyProperties())
	{
		sellCheapestProperty();
	}

	if (hasSufficientFund(amount))
	{
		balance -= amount;
	}
	else
	{
		resigned = true;
		std::cout << GlobalConstants::gameLostMessage.c_str();
	}
}

void Player::setSkipTurn(bool value)
{
	skipTurn = value;
}

bool Player::hasAnyProperties() const
{
	return properties.size() != 0;
}

bool Player::hasAllPropertiesOfColor(const MyString& color)
{
	int cnt = 0;

	for (int i = 0; i < properties.size(); i++)
	{
		if (properties[i].getColor() == color)
		{
			cnt++;
		}
	}
	
	return cnt == 4;
}

void Player::addProperty(const Property* property)
{
	properties.push_back(*property);
}

Property* Player::getProperty(int index)
{
	for (int i = 0; i < properties.size(); i++)
	{
		if (properties[i].getFieldIndex() == index)
		{
			return &properties[i];
		}
	}

	return nullptr;
}

const MyString& Player::getName() const
{
	return playerName;
}

int Player::getBalance() const
{
	return balance;
}

int Player::getPairsCount() const
{
	return pairsCount;
}

int Player::getPlayerIndex() const
{
	return playerIndex;
}

void Player::throwsPair()
{
	pairsCount++;
}

void Player::resetPairsCount()
{
	pairsCount = 0;
}

void Player::sellProperty(int fieldIndex)
{
	int i = 0;
	for (; i < properties.size(); i++)
	{
		if (properties[i].getFieldIndex() == fieldIndex)
		{
			increaseBalance(properties[i].getBasePurchaseValue());
			properties[i].removeOwner();
		}
	}

	properties.erase(i);
}

void Player::sellCheapestProperty()
{
	if (properties.size() == 0)
	{
		throw std::invalid_argument("You do not have any properties!");
	}

	int minIndex = 0;
	int minPrice = properties[0].getBasePurchaseValue();

	for (int i = 1; i < properties.size(); ++i)
	{
		int currentPrice = properties[i].getBasePurchaseValue();

		if (currentPrice < minPrice)
		{
			minPrice = currentPrice;
			minIndex = i;
		}
	}

	properties[minIndex];
	increaseBalance(properties[minIndex].getBasePurchaseValue());
	properties[minIndex].removeOwner();

	std::cout << "You have sold: ";
	properties[minIndex].printInfo();

	properties.erase(minIndex);
}

void Player::printPlayerDetails() const
{
	std::cout << playerIndex << " " << playerName << " | field: " << currentFieldIndex << " | " << "balance: " << balance << "$ | propertiesCount: " << properties.size() << std::endl;
	
	for (int i = 0; i < properties.size(); i++)
	{
		properties[i].printInfo();
	}
}

void Player::printPlayerSummary() const
{
	std::cout << playerIndex << " " << playerName << " | field: " << currentFieldIndex << " | " << "balance: " << balance << "$ | properties: ";

	for (int i = 0; i < properties.size(); i++)
	{
		std::cout << properties[i].getFieldIndex() << " ";
	}

	std::cout << std::endl;
}

void Player::buyProperty(const Property* property)
{
	reduceBalance(property->getBasePurchaseValue());
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

    const Mortgage* m = property->getMortgage();

	if (m->isCastle())
	{
		throw std::invalid_argument("Cannot buy a mortgage twice!");
	}

	reduceBalance(property->getBaseCastleValue());
	property->addMortgage(new Castle());
}

void Player::buyCottage(Property* property)
{
	if (hasAllPropertiesOfColor(property->getColor()))
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

	reduceBalance(property->getBaseCottageValue());
	property->addMortgage(new Cottage());
}

int Player::getCurrentFieldIndex() const
{
	return currentFieldIndex;
}

bool Player::hasSufficientFund(int debt) const
{
	return balance - debt >= 0;
}

bool Player::owsProperty(int fieldIndex) const
{
	for (int i = 0; i < properties.size(); i++)
	{
		if (properties[i].getFieldIndex() == fieldIndex) 
		{
			return true;
		}
	}

	return false;
}

bool Player::hasResigned() const
{
	return resigned;
}

bool Player::shouldSkipTurn() const
{
	return skipTurn;
}

void Player::saveToBin(std::ofstream& ofs) const
{
	ofs.write(reinterpret_cast<const char*>(&resigned), sizeof(resigned));
	ofs.write(reinterpret_cast<const char*>(&skipTurn), sizeof(skipTurn));
	ofs.write(reinterpret_cast<const char*>(&balance), sizeof(balance));
	ofs.write(reinterpret_cast<const char*>(&pairsCount), sizeof(pairsCount));
	ofs.write(reinterpret_cast<const char*>(&playerIndex), sizeof(playerIndex));
	ofs.write(reinterpret_cast<const char*>(&currentFieldIndex), sizeof(currentFieldIndex));

	FileFunctions::writeStringToBinFile(ofs, playerName);
}
