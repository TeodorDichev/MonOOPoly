#pragma once
#include "Field.h"
class GoToJailField : public Field
{
public:
	GoToJailField();
	GoToJailField(int index, const MyString& description);

	void interactWithField(Player* player) override;
	void printInfo() const override;
};
