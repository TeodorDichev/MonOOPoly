#pragma once
#include "MyString.h"
#include "GlobalFunctionsAndConstants.h"

#include "../Entities/Fields/Property.h"
#include "../Entities/Fields/StartField.h"
#include "../Entities/Fields/FreeParkingField.h"
#include "../Entities/Fields/GoToJailField.h"
#include "../Entities/Fields/JailField.h"
#include "../Entities/Fields/CardField.h"

#include "../Entities/Cards/GroupPaymentCard.h"
#include "../Entities/Cards/PaymentCard.h"
#include "../Entities/Cards/MovePositionCard.h"

#include "../Entities/Bank.h"
#include "../Entities/Board.h"

class SerializeFunctions
{
private:
	static Board* board;
	static Bank* bank;

public:
	static void saveGameToFile();
	static void loadGameFromFile();

	static void startNewGame();
	static void printHelp();

private:
	static void loadFieldsTxt(std::ifstream& fieldsStream);
	static void loadFieldsBin();
	static void loadCardsTxt(std::ifstream& cardsStream);
	static void loadCardsBin();

	static void writeStringToBinFile(std::ofstream& ofs, const MyString& str);
	static MyString readStringFromBinFile(std::ifstream& ifs);
};
