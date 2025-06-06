#pragma once
#include "MyString.h"

namespace GlobalFunctionsAndConstants
{
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
	const static MyString cannotBuyAnotherPlayerProperty;
	const static MyString insufficientFunds;
};
