#pragma once
#include "../Player.h"

class Field
{
protected:
	int index;

public:
	Field();
	Field(int index);
	virtual ~Field() = default;

	virtual void interactWithField(Player* player) = 0; // Visitor Pattern
};
