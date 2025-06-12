#include "../../../Headers/Entities/Fields/StartField.h"

StartField::StartField() : Field()
{ }

StartField::StartField(int index, const MyString& description) : Field(index, description)
{ }

Field* StartField::clone() const
{
	return new StartField(*this);
}

void StartField::printInfo() const
{
	std::cout << index << ", Start: moving past this tile grands you 200$" << std::endl;
}

void StartField::interactWithField(Player* player)
{
	return;
}

bool StartField::isJail() const
{
	return false;
}
