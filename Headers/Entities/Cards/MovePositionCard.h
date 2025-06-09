#pragma once
#include "Card.h"

class MovePositionCard : public Card
{
private:
	int positions;

public:
	MovePositionCard() = default;
	MovePositionCard(int positions);

	Card* clone() const override;

	void printCardDescription() const override;
	void applyEffect(Player& player) const override;
};
