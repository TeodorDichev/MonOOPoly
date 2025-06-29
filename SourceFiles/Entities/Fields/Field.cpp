#include "../../../Headers/Entities/Fields/Field.h"

Field::Field() : Field(-1, "Exampl")
{ }

Field::Field(int index, const MyString& content) : index(index), content(content)
{ }

int Field::getFieldIndex() const
{
	return index;
}

MyString Field::fieldEdge(bool draw)
{
	return draw ? "+" + MyString::repeatChar(GlobalConstants::fieldWidth, '-') 
		: MyString::repeatChar(GlobalConstants::fieldWidth + 1, ' ');
}

MyString Field::printContent() const
{
	return content + "|";
}
