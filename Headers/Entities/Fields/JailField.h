#pragma once
#include "Field.h"
class JailField : public Field
{
private:
	int tax;

public:
	JailField();
	JailField(int index, const MyString& description);

	int getPrizonTax() const;

	void interactWithField(Player* player) override;
	void printInfo() const override;
};
