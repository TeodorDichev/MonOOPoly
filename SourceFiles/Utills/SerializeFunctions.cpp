#include "../../Headers/Utills/SerializeFunctions.h"

static size_t getFileSize(std::ifstream& ifs)
{
	size_t currPos = ifs.tellg();
	ifs.seekg(0, std::ios::end);
	size_t size = ifs.tellg();
	ifs.seekg(currPos, std::ios::beg);
	return size;
}

void SerializeFunctions::saveGameToFile()
{
}

void SerializeFunctions::loadGameFromFile()
{
}

void SerializeFunctions::loadDefaultFieldsFromFile()
{
}

void SerializeFunctions::printRules()
{
}

void SerializeFunctions::writeStringToFile(std::ofstream& ofs, const MyString& str)
{
}

MyString SerializeFunctions::readStringFromFile(std::ifstream& ifs)
{
	return MyString();
}
