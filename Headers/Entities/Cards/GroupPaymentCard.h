#pragma once
#include "Card.h"
#include "../Bank.h"

class GroupPaymentCard : public Card
{
private:
	int amount;

public:
	GroupPaymentCard();
	GroupPaymentCard(int amount);

	Card* clone() const override;

	void printCardDescription() const override;
	void applyEffect(Player& player) const override;
};
