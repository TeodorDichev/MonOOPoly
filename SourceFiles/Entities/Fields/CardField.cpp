#include "../../../Headers/Entities/Fields/CardField.h"

CardField::CardField() : Field()
{ }

CardField::CardField(int index, const MyString& description) : Field(index, description)
{ }

void CardField::printInfo() const
{
	std::cout << index << ", CardField: " << description << std::endl;
}

void CardField::interactWithField(Player* player)
{
	this->deck->drawCard(player);
}
