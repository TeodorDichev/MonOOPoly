#pragma once
#include "../Utills/MyVector.hpp"
#include "../Utills/MyString.h"
#include "../Utills/GlobalConstantsAndFunctions.h"

#include "Fields/Property.h"

class Player
{
private:
	bool resigned = false;
	bool skipTurn = false;

	int balance = 0;
	int pairsCount = 0;
	int playerIndex;
	int currentFieldIndex = 0;

	MyString colorCode;
	MyString playerName;

	// This imitates shared_ptrs, and it is save as long as I manage dynamic memory
	MyVector<Property*> propertiesPtrs;

public:
	Player();
	Player(int playerIndex, const MyString& playerName, const MyString& color, int playerBalance);
	Player(int playerIndex, const MyString& playerName, const MyString& color, int playerBalance, bool resigned, bool skipTurn, int pairsCount, int currentFieldIndex);

	void resign();
	void throwsPair();
	void resetPairsCount();
	void setSkipTurn(bool value);

	bool hasAnyProperties() const;
	bool hasAllPropertiesOfColor(const MyString& color);
	bool hasSufficientFund(int debt) const;
	bool owsProperty(int fieldIndex) const;
	bool hasResigned() const;
	bool shouldSkipTurn() const;

	void addProperty(Property* property);
	void removeProperty(int index);
	Property* getProperty(int index);

	const MyString& getName() const;
	const MyString& getColorCode() const;
	int getPairsCount() const;
	int getPlayerIndex() const;
	int getCurrentFieldIndex() const;

	void moveWith(int positions);
	void moveTo(int index);

	void increaseBalance(int amount);
	void reduceBalance(int amount);

	void sellProperty(int fieldIndex);
	void sellCheapestProperty();

	void printPlayerDetails() const;
	void printPlayerSummary() const;

	void saveToBin(std::ofstream& ofs) const;
};
