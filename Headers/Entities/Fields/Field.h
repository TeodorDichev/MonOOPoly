#pragma once
#include "../Player.h"

class Field
{
protected:
	int index;
	MyString description;

public:
	Field();
	Field(int index, const MyString& description);
	virtual ~Field() = default;

	int getFieldIndex() const;
	virtual void interactWithField(Player* player) = 0;
	virtual void printInfo() const = 0;
};
