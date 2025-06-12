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

void GoToJailField::saveToBin(std::ofstream& ofs) const
{
	int type = (int)FieldType::goToJail;
	ofs.write(reinterpret_cast<const char*>(&type), sizeof(type));
	ofs.write(reinterpret_cast<const char*>(&index), sizeof(index));
	FileFunctions::writeStringToBinFile(ofs, content);

	ofs.write(reinterpret_cast<const char*>(&jailFieldIndex), sizeof(jailFieldIndex));
}
