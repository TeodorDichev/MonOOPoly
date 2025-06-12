#pragma once
#include "MyString.h"

namespace GlobalConstants
{
	static constexpr int fieldWidth = 6;
	static constexpr int fieldHeight = 1;

	static constexpr int tableSize = 11;
	
	constexpr static int startingPlayerBalance = 1500;
	constexpr static int defaultJailTax = 100;

	const static MyString helpFileName = "Help.txt";
	const static MyString fieldsFileName = "Fields.txt";
	const static MyString prevGameFields = "Fields.dat";
	const static MyString prevGamePlayers = "Players.dat";
	const static MyString cardsFileName = "Cards.txt";
	const static MyString gameLostMessage = "You have insufficient funds to execute this action and no more properties to sell due to this you have lost!";
};

namespace ExceptionMessages
{
	const static MyString notStartedGame = "You must start a game in order to be able to execute this command!";
	const static MyString playerNotFound = "Player with this index was not found!";
	const static MyString invalidFieldIndex = "Fields start from 0 to 39. Make sure to enter valid index!";
	const static MyString cannotBuyPropertyTwice = "You have already bought this property!";
	const static MyString anotherPlayerProperty = "This property is owned by another player!";
	const static MyString insufficientFunds = "You have insufficient funds to execute this action!";
	const static MyString invalidMortgageName = "Invalid mortgage name!";
	const static MyString invalidTradeIndex = "Invalid trade index!";
	const static MyString invalidPlayersCount = "Invalid players count! Game must have between 2 and 6 players!";
	const static MyString failedToOpenFile = "Failed opening file!";
	const static MyString unknownFieldType = "Unknown field type has been reached!";
	const static MyString unknownCardType = "Unknown card type has been reached!";
	const static MyString noPrevGames = "There is no previous game to load!";
	const static MyString invalidCommand = "Invalid command!";
};

enum class Mortgages
{
	cottage,
	castle
};
