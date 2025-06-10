#include "../../Headers/Utills/GlobalFunctionsAndConstants.h"

const MyString GlobalFunctionsAndConstants::helpFileName = "Help.txt";
const static MyString GlobalFunctionsAndConstants::fieldsFileName = "Fields.txt";
const static MyString GlobalFunctionsAndConstants::gameLostMessage = "You have insufficient funds to execute this action and no more properties to sell due to this you have lost!";

const MyString ExceptionMessages::notStartedGame = "You must start a game in order to be able to execute this command!";
const MyString ExceptionMessages::playerNotFound = "Player with this index was not found!";
const static MyString ExceptionMessages::invalidFieldIndex = "Fields start from 0 to 39. Make sure to enter valid index!";
const static MyString ExceptionMessages::cannotBuyPropertyTwice = "You have already bought this property!";
const static MyString ExceptionMessages::anotherPlayerProperty = "This property is owned by another player!";
const static MyString ExceptionMessages::insufficientFunds = "You have insufficient funds to execute this action!";
const static MyString ExceptionMessages::invalidMortgageName = "Invalid mortgage name!";
const static MyString ExceptionMessages::invalidTradeIndex = "Invalid trade index!";
const static MyString ExceptionMessages::invalidPlayersCount = "Invalid players count! Game must have between 2 and 6 players!";
