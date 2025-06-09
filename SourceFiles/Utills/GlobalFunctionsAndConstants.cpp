#include "../../Headers/Utills/GlobalFunctionsAndConstants.h"

const MyString GlobalFunctionsAndConstants::helpFileName = "Help.txt";

const MyString ExceptionMessages::notStartedGame = "You must start a game in order to be able to execute this command!";
const MyString ExceptionMessages::playerNotFound = "Player with this index was not found!";
const static MyString ExceptionMessages::invalidFieldIndex = "Fields start from 0 to 39. Make sure to enter valid index!";
const static MyString ExceptionMessages::cannotBuyPropertyTwice = "You have already bought this property!";
const static MyString ExceptionMessages::anotherPlayerProperty = "This property is owned by another player!";
const static MyString ExceptionMessages::insufficientFunds = "You have insufficient funds to purchase this property!";
