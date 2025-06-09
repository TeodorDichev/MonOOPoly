#include "../../../Headers/Entities/Fields/Field.h"

Field::Field() : Field(-1, "")
{ }

Field::Field(int index, const MyString& description) : index(index), description(description)
{ }

int Field::getFieldIndex() const
{
	return index;
}
