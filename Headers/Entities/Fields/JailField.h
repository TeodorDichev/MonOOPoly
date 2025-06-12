#pragma once
#include "Field.h"
class JailField : public Field
{
private:
	static int tax;

public:
	JailField();
	JailField(int index, const MyString& content, int tax);
	Field* clone() const override;

	static int getJailTax();

	void interactWithField(Player* player) override;
	void printInfo() const override;

	bool isJail() const override;
	void saveToBin(std::ofstream& ofs) const override;
};
