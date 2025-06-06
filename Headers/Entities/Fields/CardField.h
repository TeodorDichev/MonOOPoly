#pragma once
#include "Field.h"
class CardField : public Field
{
public:
	CardField();
	CardField(int index);

	void interactWithField(Player* player) override;
	void printInfo() const override;
};
