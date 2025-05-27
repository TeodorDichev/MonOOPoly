#pragma once
#include "Player.h"
#include "Fields/CardField.h"

class Bank
{
public:
	void addMoneyToPlayerBalance(Player& player);
	void subtractMoneyFromPlayerBalance(Player& player);
	void buyFieldFromPlayer(Player& player, const Field& field);
};
