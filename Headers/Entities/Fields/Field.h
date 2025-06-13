#pragma once
#include "../../Utills/MyString.h"
#include "../../Utills/GlobalConstantsAndFunctions.h"

#include <fstream>

class Player;

class Field
{
protected:
	int index;
	MyString content;

public:
	Field();
	Field(int index, const MyString& content);
	virtual ~Field() = default;
	virtual Field* clone() const = 0;

	int getFieldIndex() const;
	virtual void interactWithField(Player* player) = 0;
	virtual void printInfo() const = 0;

	static MyString fieldEdge(bool draw);
	virtual MyString printContent() const;

	virtual bool isJail() const = 0;

	virtual void saveToBin(std::ofstream& ofs) const = 0;
};
