#include "../../../Headers/Entities/Fields/JailField.h"

JailField::JailField() : Field()
{ }

JailField::JailField(int index, const MyString& description, int tax) : Field(index, description)
{
	this->tax = tax;
}

void JailField::printInfo() const
{
	std::cout << index << ", JailField: " << description << std::endl;
}

int JailField::getJailTax() const
{
	return tax;
}

void JailField::interactWithField(Player* player)
{
	std::cout << "You entered jail! Your next turn will be skipped! If you want to go out you will need to pay a tax of " << tax << "$!" << std::endl;
	player->setSkipTurn(true);
}
