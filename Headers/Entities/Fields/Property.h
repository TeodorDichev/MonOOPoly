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
	Property(int index, const MyString& content, const MyString& color,
		int baseRentValue, int basePurchaseValue, int baseCottageValue, int baseCastleValue);

	int getRent() const;
	bool hasMortgage() const;
	const MyString& getColor() const;

	int getBasePurchaseValue() const;
	int getBaseCottageValue() const;
	int getBaseCastleValue() const;

	Player* getOwner() const;

	void setOwner(Player* player);
	void removeOwner();

	const Mortgage* getMortgage() const;

	void addMortgage(const Mortgage& mortgage);

	void interactWithField(Player* player) override;
	void printInfo() const override;
};
