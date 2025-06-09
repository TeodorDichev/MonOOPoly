#pragma once
#include "Field.h"
class JailField : public Field
{
private:
	int tax;

public:
	JailField();
	JailField(int index, const MyString& content, int tax);

	int getJailTax() const;

	void interactWithField(Player* player) override;
	void printInfo() const override;
};
