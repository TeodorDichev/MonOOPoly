#pragma once
#include "../Utills/MyVector.hpp"
#include "../Utills/MyString.h"
#include "../Utills/GlobalFunctionsAndConstants.h"

#include "Fields/Property.h"
#include "Fields/CardField.h"
#include "Fields/JailField.h"
#include "Fields/FreeParkingField.h"
#include "Mortgage/Cottage.h"
#include "Mortgage/Castle.h"

class Player
{
private:
	bool resigned = false;
	bool skipTurn = false;

	int balance = 0;
	int pairsCount = 0;
	int playerIndex;
	int currentFieldIndex;

	MyString playerName;
	MyVector<Property> properties;

	void buyProperty(Property* property);
	void buyCastle(Property* property);
	void buyCottage(Property* property);

public:
	Player();
	Player(int playerIndex, const MyString& playerName, int playerBalance);

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

	const MyString& getName() const;
	int getBalance() const;
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
};
