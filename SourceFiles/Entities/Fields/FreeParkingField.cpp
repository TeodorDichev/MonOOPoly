#include "../../../Headers/Entities/Fields/FreeParkingField.h"

FreeParkingField::FreeParkingField() : Field()
{ }

FreeParkingField::FreeParkingField(int index, const MyString& description) : Field(index, description)
{ }

Field* FreeParkingField::clone() const
{
	return new FreeParkingField(*this);
}

void FreeParkingField::printInfo() const
{
	std::cout << index << ", FreeParkingField" << std::endl;
}

void FreeParkingField::interactWithField(Player* player)
{
	std::cout << "Welcome! This is a free parking!";
}

bool FreeParkingField::isJail() const
{
	return false;
}

void FreeParkingField::saveToBin(std::ofstream& ofs) const
{
	int type = (int)FieldType::freeParking;
	ofs.write(reinterpret_cast<const char*>(&type), sizeof(type));
	ofs.write(reinterpret_cast<const char*>(&index), sizeof(index));
	FileFunctions::writeStringToBinFile(ofs, content);
}
