#pragma once
#include "Field.h"
#include "../Mortgage/Mortgage.h"

class Property : public Field
{
private:
	int baseRentValue;
	int basePurchaseValue;
	int baseCottageValue;
	int baseCastleValue;

	Player* owner = nullptr;

	Mortgage* mortgage = nullptr;

public:
	Property();
	Property(int index, int baseRentValue, int basePurchaseValue, int baseCottageValue, int baseCastleValue);

	void payRent() const;
	int getRent() const;

	int getBasePurchaseValue() const;
	int getBaseCottageValue() const;
	int getBaseCastleValue() const;

	Player* getOwner() const;
	void setOwner(Player* player);

	const Mortgage* getMortgage() const;

	void addMortgage(const Mortgage* mortgage);

	void interactWithField(Player* player) override; // Visitor Pattern
	void printInfo() const override;
};
