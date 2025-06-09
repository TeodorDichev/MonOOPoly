#pragma once
#include "../Utills/MyVector.hpp"
#include "Fields/Property.h"
#include "../Utills/MyString.h"
#include "Fields/CardField.h"
#include "Fields/JailField.h"
#include "Fields/FreeParkingField.h"
#include "../Utills/GlobalFunctionsAndConstants.h"
#include "Mortgage/Cottage.h"
#include "Mortgage/Castle.h"

class Player
{
private:
	bool resigned;
	bool skipTurn = false;

	int balance;
	int pairsCount;
	int playerIndex;
	int currentFieldIndex;

	MyString playerName;
	MyVector<Property> properties;

	void buyProperty(Property* property);
	void buyCastle(Property* property);
	void buyCottage(Property* property);

public:
	Player();
	Player(int playerIndex, MyString playerName, int playerBalance);

	void moveTo(Field* field);
	void setSkipTurn(bool value);

	bool hasAnyProperties() const;
	int getPropertiesWithColor(const MyString& color);
	int getBalance() const;
	int getPairsCount() const;
	int getPlayerIndex() const;
	int getCurrentFieldIndex() const;
	bool hasSufficientFund(int debt) const;
	bool owsProperty(int fieldIndex) const;
	bool hasResigned() const;
	bool shouldSkipTurn() const;

	void resetSkipTurn();
	void resign();

	void throwsPair();
	void resetPairsCount();

	void addToBalance(int amount);
	void sellProperty(int fieldIndex);
	void sellCheapestProperty();

	void visit(Property* field);

	void printCurrentPosition() const;
	void printPlayerDetails() const;
};
