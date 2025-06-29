#include "../../../Headers/Entities/Fields/CardField.h"

CardField::CardField() : Field()
{ }

CardField::CardField(int index, const MyString& description, const CardDeck* ptr) : Field(index, description)
{ 
	deck = ptr;
}

Field* CardField::clone() const
{
	return new CardField(*this);
}

void CardField::printInfo() const
{
	std::cout << index << ", CardField" << std::endl;
}

bool CardField::isJail() const
{
	return false;
}

void CardField::interactWithField(Player* player)
{
	printInfo();
	this->deck->drawCard(player);
}

void CardField::saveToBin(std::ofstream& ofs) const
{
	int type = (int) FieldType::card;
	ofs.write(reinterpret_cast<const char*>(&type), sizeof(type));
	ofs.write(reinterpret_cast<const char*>(&index), sizeof(index));
	FileFunctions::writeStringToBinFile(ofs, content);
}
