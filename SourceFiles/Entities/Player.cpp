#include "../../Headers/Entities/Player.h"

Player::Player() : Player(-1, "", GlobalConstants::defaultColorCode, 0)
{ }

Player::Player(int playerIndex, const MyString& playerName, const MyString& color, int playerBalance) 
	: playerIndex(playerIndex), playerName(playerName), balance(playerBalance), colorCode(color)
{ }

Player::Player(int playerIndex, const MyString& playerName, const MyString& color, int playerBalance, bool resigned, bool skipTurn, int pairsCount, int currentFieldIndex)
	: Player(playerIndex, playerName, color, playerBalance)
{
	this->resigned = resigned;
	this->skipTurn = skipTurn;
	this->pairsCount = pairsCount;
	this->currentFieldIndex = currentFieldIndex;
}

bool Player::hasResigned() const
{
	return resigned;
}

bool Player::shouldSkipTurn() const
{
	return skipTurn;
}

void Player::increaseBalance(int amount)
{
	balance += amount;
}

void Player::setSkipTurn(bool value)
{
	skipTurn = value;
}

bool Player::hasAnyProperties() const
{
	return propertiesPtrs.size() != 0;
}

const MyString& Player::getName() const
{
	return playerName;
}

const MyString& Player::getColorCode() const
{
	return colorCode;
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
	for (int i = 0; i < propertiesPtrs.size(); i++)
	{
		if (propertiesPtrs[i]->getFieldIndex() == fieldIndex)
		{
			return true;
		}
	}

	return false;
}

void Player::moveTo(int index)
{
	currentFieldIndex = index;
}

void Player::moveWith(int positions)
{
	int newIndex = currentFieldIndex + positions;

	if (newIndex / GlobalConstants::defaultBoardSize != 0)
	{
		newIndex %= GlobalConstants::defaultBoardSize;
		increaseBalance(GlobalConstants::defaultStartIncrease);
		std::cout << "Moving past start grands you 200$" << std::endl;
	}

	currentFieldIndex = newIndex;
}

void Player::resign()
{
	resigned = true;
	
	for (int i = 0; i < propertiesPtrs.size(); i++)
	{
		propertiesPtrs[i]->removeOwner();
		if (propertiesPtrs[i]->hasBuilding())
		{
			propertiesPtrs[i]->removeBuilding();
		}
	}
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
		std::cout << GlobalConstants::gameLostMessage.c_str() << std::endl;

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Press anything to continue...";
		std::cin.get();
	}
}

bool Player::hasAllPropertiesOfColor(const MyString& color)
{
	int cnt = 0;

	for (int i = 0; i < propertiesPtrs.size(); i++)
	{
		if (propertiesPtrs[i]->getColor() == color)
		{
			cnt++;
		}
	}
	
	return cnt == 4;
}

void Player::addProperty(Property* property)
{
	propertiesPtrs.push_back(property);
}

void Player::removeProperty(int index)
{
	for (int i = 0; i < propertiesPtrs.size(); i++)
	{
		if (propertiesPtrs[i]->getFieldIndex() == index)
		{
			propertiesPtrs.erase(i);
			break;
		}
	}
}

Property* Player::getProperty(int index)
{
	for (int i = 0; i < propertiesPtrs.size(); i++)
	{
		if (propertiesPtrs[i]->getFieldIndex() == index)
		{
			return propertiesPtrs[i];
		}
	}

	return nullptr;
}

void Player::sellProperty(int fieldIndex)
{
	for (int i = 0; i < propertiesPtrs.size(); i++)
	{
		if (propertiesPtrs[i]->getFieldIndex() == fieldIndex)
		{
			increaseBalance(propertiesPtrs[i]->getBasePurchaseValue());
			propertiesPtrs[i]->removeOwner();
			propertiesPtrs.erase(i);
			return;
		}
	}
}

void Player::sellCheapestProperty()
{
	if (propertiesPtrs.size() == 0)
	{
		throw std::invalid_argument(ExceptionMessages::noPropertiesToSell.c_str());
	}

	int minIndex = 0;
	int minPrice = propertiesPtrs[0]->getBasePurchaseValue();

	for (int i = 1; i < propertiesPtrs.size(); ++i)
	{
		int currentPrice = propertiesPtrs[i]->getBasePurchaseValue();

		if (currentPrice < minPrice)
		{
			minPrice = currentPrice;
			minIndex = i;
		}
	}

	increaseBalance(propertiesPtrs[minIndex]->getBasePurchaseValue());
	propertiesPtrs[minIndex]->removeOwner();

	std::cout << playerName << " have sold: ";
	propertiesPtrs[minIndex]->printInfo();

	propertiesPtrs.erase(minIndex);
}

void Player::printPlayerDetails() const
{
	std::cout << colorCode << playerIndex << " " << playerName << " | field: " << currentFieldIndex << " | " << "balance: " << balance << "$ | propertiesCount: " << propertiesPtrs.size() << std::endl;
	
	for (int i = 0; i < propertiesPtrs.size(); i++)
	{
		propertiesPtrs[i]->printInfo();
	}

	std::cout << GlobalConstants::defaultColorCode;
}

void Player::printPlayerSummary() const
{
	if (resigned)
	{
		std::cout << GlobalConstants::strikeThroughCode << colorCode << playerIndex << " " << playerName << GlobalConstants::defaultColorCode << std::endl;
		return;
	}
	
	std::cout << colorCode << playerIndex << " " << playerName << " | field: " << currentFieldIndex << " | " << "balance: " << balance << "$ | properties: ";

	for (int i = 0; i < propertiesPtrs.size(); i++)
	{
		std::cout << propertiesPtrs[i]->getFieldIndex() << " ";
	}

	std::cout << GlobalConstants::defaultColorCode;

	std::cout << std::endl;
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
	FileFunctions::writeStringToBinFile(ofs, colorCode);
}
