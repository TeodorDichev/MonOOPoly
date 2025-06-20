#pragma once
#include "Card.h"
#include "../Board.h"

class GroupPaymentCard : public Card
{
private:
	int amount;

public:
	GroupPaymentCard() = default;
	GroupPaymentCard(int amount);

	Card* clone() const override;

	void printCardDescription() const override;
	void applyEffect(Player& player) const override;
};
