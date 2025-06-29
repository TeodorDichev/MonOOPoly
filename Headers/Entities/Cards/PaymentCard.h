#pragma once
#include "Card.h"
#include "../../../Headers/Entities/Player.h"

class PaymentCard : public Card
{
private:
	int amount;

public:
	PaymentCard() = default;
	PaymentCard(int amount);

	Card* clone() const override;

	void printCardDescription() const override;
	void applyEffect(Player& player) const override;
};
