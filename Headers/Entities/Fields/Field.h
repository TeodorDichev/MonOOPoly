#pragma once
#include "../Player.h"

class Field
{
protected:
	int index;
	MyString content;

public:
	Field();
	Field(int index, const MyString& content);
	virtual ~Field() = default;

	int getFieldIndex() const;
	virtual void interactWithField(Player* player) = 0;
	virtual void printInfo() const = 0;

	MyString& getContentRef();

	static MyString fieldEdge(bool draw);
	MyString printContent() const;
};
