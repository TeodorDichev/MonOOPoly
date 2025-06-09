#pragma once
#include "Field.h"
class GoToJailField : public Field
{
private:
	int jailFieldIndex;

public:
	GoToJailField();
	GoToJailField(int index, const MyString& description, int jailIndex);

	void interactWithField(Player* player) override;
	void printInfo() const override;
};
