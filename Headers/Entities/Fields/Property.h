#pragma once
#include "Field.h"
#include "../Mortgage/Castle.h"
#include "../Mortgage/Cottage.h"

class Player;

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

	Field* clone() const override;

	int getRent() const;
	bool hasMortgage() const;
	const MyString& getColor() const;

	int getBasePurchaseValue() const;
	int getBaseCottageValue() const;
	int getBaseCastleValue() const;

	void setOwner(Player* player);
	void removeOwner();

	const Mortgage* getMortgage() const;

	void addMortgage(const Mortgage* mortgage);

	void interactWithField(Player* player) override;
	void printInfo() const override;

	bool isJail() const override;
};
