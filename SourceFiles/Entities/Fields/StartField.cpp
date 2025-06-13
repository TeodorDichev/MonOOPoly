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
	printInfo();
}

bool StartField::isJail() const
{
	return false;
}

void StartField::saveToBin(std::ofstream& ofs) const
{
	int type = (int)FieldType::start;
	ofs.write(reinterpret_cast<const char*>(&type), sizeof(type));

	ofs.write(reinterpret_cast<const char*>(&index), sizeof(index));
	FileFunctions::writeStringToBinFile(ofs, content);
}
