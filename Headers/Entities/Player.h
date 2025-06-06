#pragma once
#include "../Utills/MyVector.hpp"
#include "Fields/Property.h"
#include "../Utills/MyString.h"
#include "Fields/CardField.h"
#include "Fields/JailField.h"
#include "Fields/FreeParkingField.h"
#include "../Utills/GlobalFunctionsAndConstants.h"

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

public:
	Player();
	Player(int playerIndex, MyString playerName, int playerBalance);

	int getBalance() const;
	int getPairsCount() const;
	int getPlayerIndex() const;
	int getCurrentFieldIndex() const;
	bool hasSufficientFund(int debt) const;
	bool owsProperty(int fieldIndex) const;
	bool hasResigned() const;
	bool shouldSkipTurn() const;

	void resetSkipTurn();
	void Resign();

	void setCurrentFieldIndex(int value);
	void throwsPair();
	void resetPairsCount();

	void addToBalance(int amount);
	void addProperty(Property* Property);
	void removeProperty(Property* Property);
	void sellCheapestProperty();

	void visit(const CardField* field);
	void visit(const JailField* field);
	void visit(Property* field);
	void visit(const FreeParkingField* field);

	void printCurrentPosition() const;
	void printPlayerDetails() const;
};
