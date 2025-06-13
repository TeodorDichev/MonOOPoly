#pragma once
#include "MyString.h"

namespace GlobalConstants
{
	static constexpr int fieldWidth = 6;
	static constexpr int fieldHeight = 1;

	static constexpr int tableSize = 11;
	static constexpr int defaultBoardSize = 40;
	
	constexpr static int startingPlayerBalance = 1500;
	constexpr static int defaultJailTax = 100;

	const static MyString defaultColorCode = "\033[0m";
	const static MyString colorCodeBase = "\033[3";
	const static MyString strikeThroughCode = "\033[9m";

	const static MyString clearConsoleCode = "cls";

	const static MyString helpFileName = "Help.txt";
	const static MyString cardsFileName = "Cards.txt";
	const static MyString fieldsFileName = "Fields.txt";

	const static MyString prevGameTradesFile = "Trades.dat";
	const static MyString prevGameFieldsFile = "Fields.dat";
	const static MyString prevGamePlayersFile = "Players.dat";

	const static MyString gameLostMessage = "You have insufficient funds to execute this action and no more properties to sell due to this you have lost!";
};

namespace ExceptionMessages
{
	const static MyString invalidCommand = "Invalid command!";
	const static MyString failedToOpenFile = "Failed opening file!";
	const static MyString invalidTradeIndex = "Invalid trade index!";
	const static MyString invalidMortgageName = "Invalid mortgage name!";
	const static MyString noPrevGames = "There is no previous game to load!";
	const static MyString unknownCardType = "Unknown card type has been reached!";
	const static MyString playerNotFound = "Player with this index was not found!";
	const static MyString unknownFieldType = "Unknown field type has been reached!";
	const static MyString cannotBuyMortgageTwice = "You have already bought mortgage!";
	const static MyString cannotBuyPropertyTwice = "You have already bought this property!";
	const static MyString anotherPlayerProperty = "This property is owned by another player!";
	const static MyString insufficientFunds = "You have insufficient funds to execute this action!";
	const static MyString invalidFieldIndex = "Fields start from 0 to 39. Make sure to enter valid index!";
	const static MyString invalidCastlePurchase = "To buy a castle you need to have a cottage on the property!";
	const static MyString notStartedGame = "You must start a game in order to be able to execute this command!";
	const static MyString invalidPlayersCount = "Invalid players count! Game must have between 2 and 6 players!";
	const static MyString invalidCottagePurchase = "To buy a cottage you need to own all properties of certain color!";
};

namespace FileFunctions
{
	void writeStringToBinFile(std::ofstream& ofs, const MyString& str);
	MyString readStringFromBinFile(std::ifstream& ifs);
}

enum class MortgageType
{
	cottage = 0,
	castle = 1
};

enum class CardType
{
	move = 0,
	payment = 1,
	groupPayment = 2
};

enum class FieldType
{
	start = 0,
	property = 1,
	card = 2,
	goToJail = 3,
	jail = 4,
	freeParking = 5
};
