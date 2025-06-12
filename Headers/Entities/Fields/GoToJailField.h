#pragma once
#include "Field.h"

class GoToJailField : public Field
{
private:
	int jailFieldIndex;

public:
	GoToJailField();
	GoToJailField(int index, const MyString& content, int jailIndex);
	Field* clone() const override;

	void interactWithField(Player* player) override;
	void printInfo() const override;

	bool isJail() const override;
	void saveToBin(std::ofstream& ofs) const override;
};
