#pragma once
#include "MyString.h"
#include "GlobalConstantsAndFunctions.h"

#include "../Entities/Bank.h"
#include "../Entities/Board.h"

#include<fstream>

class SerializeFunctions
{
public:
	static void saveGameToFile();
	static void loadGameFromFile();

	static void startNewGame();
	static void printHelp();

private:
	static Board* board;
	static Bank* bank;

	static void loadFieldsTxt(std::ifstream& ifs);
	static void loadCardsTxt(std::ifstream& ifs);

	static void loadFieldsBin(std::ifstream& ifs);
	static void loadPlayersBin(std::ifstream& ifs);
	static void loadTradesBin(std::ifstream& ifs);
};
