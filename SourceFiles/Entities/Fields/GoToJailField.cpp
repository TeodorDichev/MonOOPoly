#include "../../../Headers/Entities/Fields/GoToJailField.h"

GoToJailField::GoToJailField() : Field()
{ }

GoToJailField::GoToJailField(int index, const MyString& description, int jailIndex) : Field(index, description)
{ 
	this->jailFieldIndex = jailIndex;
}

void GoToJailField::printInfo() const
{
	std::cout << index << ", GoToJailField: " << description << std::endl;
}

void GoToJailField::interactWithField(Player* player)
{
	player->moveTo(jailFieldIndex);
}
