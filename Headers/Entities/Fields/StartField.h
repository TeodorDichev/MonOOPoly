#pragma once
#include "Field.h"

class StartField : public Field
{
public:
	StartField();
	StartField(int index, const MyString& content);
	Field* clone() const override;

	void interactWithField(Player* player) override;
	void printInfo() const override;

	bool isJail() const override;

};

