#pragma once
#include "Field.h"

class FreeParkingField : public Field
{
public:
	FreeParkingField();
	FreeParkingField(int index, const MyString& description);

	void interactWithField(Player* player) override;
	void printInfo() const override;
};
