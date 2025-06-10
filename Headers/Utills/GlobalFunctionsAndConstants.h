#pragma once
#include "MyString.h"

namespace GlobalFunctionsAndConstants
{
	static constexpr int fieldWidth = 6;
	static constexpr int fieldHeight = 1;

	static constexpr int tableSize = 11;
	
	constexpr static int boardSize = 40;
	constexpr static int startingPlayerBalance = 1500;
	const static MyString helpFileName;
};

namespace ExceptionMessages
{
	const static MyString notStartedGame;
	const static MyString playerNotFound;
	const static MyString invalidFieldIndex;
	const static MyString cannotBuyPropertyTwice;
	const static MyString anotherPlayerProperty;
	const static MyString insufficientFunds;
	const static MyString invalidMortgageName;
	const static MyString invalidTradeIndex;
	const static MyString invalidPlayersCount;
};

enum class Mortgages
{
	cottage,
	castle
};
