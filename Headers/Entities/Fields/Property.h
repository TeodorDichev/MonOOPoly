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

	int ownerIndex = -1;

	Mortgage* mortgage = nullptr;

public:
	Property();
	Property(int index, int baseRentValue, int basePurchaseValue, int baseCottageValue, int baseCastleValue);

	int getBaseRentValue() const;
	int getbasePurchaseValue() const;
	int getbaseCottageValue() const;
	int getbaseCastleValue() const;
	int getownerIndex() const;

	const Mortgage* getMortgage() const;

	void addMortgage(const Mortgage* mortgage);

	void interactWithField(Player* player) override;
};
