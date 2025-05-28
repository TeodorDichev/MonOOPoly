#pragma once
#include "MyString.h"
#include<fstream>

class SerializeFunctions
{
public:
	static void saveGameToFile();
	static void loadGameFromFile();
	static void loadDefaultFieldsFromFile();
	static void printRules();

private:

	static void writeStringToFile(std::ofstream& ofs, const MyString& str);
	static MyString readStringFromFile(std::ifstream& ifs);
};
