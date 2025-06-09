#include "../../../Headers/Entities/Fields/FreeParkingField.h"

FreeParkingField::FreeParkingField() : Field()
{ }

FreeParkingField::FreeParkingField(int index, const MyString& description) : Field(index, description)
{ }

void FreeParkingField::printInfo() const
{
	std::cout << index << ", FreeParkingField: " << description << std::endl;
}

void FreeParkingField::interactWithField(Player* player)
{
	std::cout << "Welcome! This is a free parking!";
}
