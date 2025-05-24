#pragma once
#include "MyString.h"
#include<fstream>

class SerializeFunctions
{
public:
	static void saveSystemToFile();
	static void loadSystemFromFile();

private:

	static void writeStringToFile(std::ofstream& ofs, const MyString& str);
	static MyString readStringFromFile(std::ifstream& ifs);
};
