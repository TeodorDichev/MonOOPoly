#pragma once
#include "../Utills/MyVector.hpp"
#include "Fields/Property.h"
#include "../Utills/MyString.h"
#include "Fields/CardField.h"
#include "Fields/JailField.h"
#include "Fields/FreeParkingField.h"

class Player
{
private:
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
	bool owsProperty(const Property* property) const;

	void setCurrentFieldIndex(int value);
	void throwsPair();

	void addToBalance(int amount);
	void addProperty(Property* Property);
	void removeProperty(Property* Property);

	void visit(const CardField* field);
	void visit(const JailField* field);
	void visit(const Property* field);
	void visit(const FreeParkingField* field);

	void printCurrentPosition() const;
	void printPlayerDetails() const;
};
