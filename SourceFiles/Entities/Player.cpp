#include "../../Headers/Entities/Player.h"

void Player::setCurrentFieldIndex(int value)
{
	currentFieldIndex = value;
}

void Player::throwsPair()
{
	pairsCount > 3 ? pairsCount = 0 : pairsCount++;
}

void Player::addToBalance(int amount)
{
	balance += amount;
}
