#pragma once
#include "MyString.h"
#include "GlobalConstantsAndFunctions.h"

#include "../Entities/Bank.h"
#include "../Entities/Board.h"

#include "../Entities/Fields/Property.h"
#include "../Entities/Fields/StartField.h"
#include "../Entities/Fields/FreeParkingField.h"
#include "../Entities/Fields/GoToJailField.h"
#include "../Entities/Fields/JailField.h"
#include "../Entities/Fields/CardField.h"

#include "../Entities/Cards/GroupPaymentCard.h"
#include "../Entities/Cards/PaymentCard.h"
#include "../Entities/Cards/MovePositionCard.h"

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
