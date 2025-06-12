#include "../../../Headers/Entities/Fields/JailField.h"
#include "../../../Headers/Entities/Player.h"

int JailField::tax = GlobalConstants::defaultJailTax;

JailField::JailField() : Field()
{ }

JailField::JailField(int index, const MyString& description, int tax) : Field(index, description)
{
	this->tax = tax;
}

Field* JailField::clone() const
{
	return new JailField(*this);
}

void JailField::printInfo() const
{
	std::cout << index << ", JailField: Your next turn will be skipped! If you want to go out you will need to pay a tax of " << tax << "$!" << std::endl;
}

int JailField::getJailTax()
{
	return tax;
}

void JailField::interactWithField(Player* player)
{
	player->setSkipTurn(true);
}

bool JailField::isJail() const
{
	return true;
}
