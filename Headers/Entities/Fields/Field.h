#pragma once
#include "../../Utills/MyString.h"

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

	MyString& getContentRef();

	static MyString fieldEdge(bool draw);
	MyString printContent() const;

	virtual bool isJail() const = 0;
};
