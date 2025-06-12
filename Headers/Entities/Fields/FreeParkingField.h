#pragma once
#include "Field.h"

class FreeParkingField : public Field
{
public:
	FreeParkingField();
	FreeParkingField(int index, const MyString& content);
	Field* clone() const override;

	void interactWithField(Player* player) override;
	void printInfo() const override;

	bool isJail() const override;
	void saveToBin(std::ofstream& ofs) const override;
};
