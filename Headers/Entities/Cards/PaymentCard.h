#pragma once
#include "Card.h"
class PaymentCard : public Card
{
private:
	int amount;

public:
	PaymentCard();
	PaymentCard(const MyString& description, int amount);

	Card* clone() const override;

	void printCardDescription() const override;
	void applyEffect(Player& player) override;
};
