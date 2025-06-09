#include "../../../Headers/Entities/Fields/GoToJailField.h"

GoToJailField::GoToJailField() : Field()
{ }

GoToJailField::GoToJailField(int index, const MyString& description) : Field(index, description)
{ }

void GoToJailField::printInfo() const
{
	std::cout << index << ", GoToJailField: " << description << std::endl;
}

void GoToJailField::interactWithField(Player* player)
{
	// TO DO 
	// moveTo(jail)
}
