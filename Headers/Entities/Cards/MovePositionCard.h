#pragma once
#include "Card.h"

class MovePositionCard : public Card
{
private:
	int positions;

public:
	MovePositionCard();
	MovePositionCard(const MyString& description, int positions);

	Card* clone() const override;

	void printCardDescription() const override;
	void applyEffect(Player& player) override;
};
