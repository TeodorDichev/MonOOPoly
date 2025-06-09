#pragma once
#include "Field.h"

class Mortgage;

class Property : public Field
{
private:
	int baseRentValue;
	int basePurchaseValue;
	int baseCottageValue;
	int baseCastleValue;

	MyString color;

	Player* owner = nullptr;

	Mortgage* mortgage = nullptr;

public:
	Property();
	Property(int index, const MyString& description, const MyString& color, 
		int baseRentValue, int basePurchaseValue, int baseCottageValue, int baseCastleValue);

	void payRent() const;
	int getRent() const;
	bool hasMortgage() const;
	const MyString& getColor() const;

	int getBasePurchaseValue() const;
	int getBaseCottageValue() const;
	int getBaseCastleValue() const;

	Player* getOwner() const;
	void setOwner(Player* player);

	const Mortgage* getMortgage() const;

	void addMortgage(Mortgage& mortgage);

	void interactWithField(Player* player) override; // Visitor Pattern
	void printInfo() const override;
};
