#pragma once
#include "Field.h"
#include "../Buildings/Castle.h"
#include "../Buildings/Cottage.h"

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

	Building* building = nullptr;

public:
	Property();
	Property(int index, const MyString& content, const MyString& color,
		int baseRentValue, int basePurchaseValue, int baseCottageValue, int baseCastleValue);

	Field* clone() const override;

	int getRent() const;
	bool hasBuilding() const;
	const MyString& getColor() const;

	int getBasePurchaseValue() const;
	int getBaseCottageValue() const;
	int getBaseCastleValue() const;

	void setOwner(Player* player);
	void removeOwner();

	const Building* getBuilding() const;
	void removeBuilding();
	void addBuilding(const Building& building);

	void interactWithField(Player* player) override;
	void printInfo() const override;

	bool isJail() const override;

	MyString printContent() const override;

	void saveToBin(std::ofstream& ofs) const override;
};
