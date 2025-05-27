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

	int getFieldIndex() const;
	virtual void interactWithField(Player* player) = 0; // Visitor Pattern
};
