#pragma once
#include "Field.h"
class JailField : public Field
{
private:
	int tax;

public:
	JailField();
	JailField(int index, int tax);

	int getPrizonTax() const;

	void interactWithField(Player* player) override;
	void printInfo() const override;
};
