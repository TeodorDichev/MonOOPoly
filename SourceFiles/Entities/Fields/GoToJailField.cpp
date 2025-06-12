#include "../../../Headers/Entities/Fields/GoToJailField.h"
#include "../../../Headers/Entities/Player.h"

GoToJailField::GoToJailField() : Field()
{ 
	this->jailFieldIndex = -1;
}

GoToJailField::GoToJailField(int index, const MyString& description, int jailIndex) : Field(index, description)
{ 
	this->jailFieldIndex = jailIndex;
}

Field* GoToJailField::clone() const
{
	return new GoToJailField(*this);
}

void GoToJailField::printInfo() const
{
	std::cout << index << ", GoToJailField" << std::endl;
}

void GoToJailField::interactWithField(Player* player)
{
	player->moveTo(jailFieldIndex);
}

bool GoToJailField::isJail() const
{
	return false;
}
