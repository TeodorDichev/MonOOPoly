#pragma once
#include "Field.h"

class FreeParkingField : public Field
{
public:
	FreeParkingField();
	FreeParkingField(int index);

	void interactWithField(Player* player) override;
	void printInfo() const override;
};
