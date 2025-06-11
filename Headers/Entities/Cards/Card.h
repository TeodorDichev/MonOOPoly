#pragma once

class Player;

class Card
{
public:
	Card() = default;
	virtual ~Card() = default;

	virtual Card* clone() const = 0;

	virtual void printCardDescription() const = 0;
	virtual void applyEffect(Player& player) const = 0;
};
