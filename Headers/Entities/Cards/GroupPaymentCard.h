#pragma once
#include "Card.h"
class GroupPaymentCard : public Card
{
private:
	int amount;

public:
	GroupPaymentCard();
	GroupPaymentCard(const MyString& description, int amount);

	Card* clone() const override;

	void printCardDescription() const override;
	void applyEffect(Player& player) override;
};
