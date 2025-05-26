#pragma once
#include "../Player.h"
#include "../../Utills/MyString.h"

class Card
{
protected:
	MyString cardDescription;

public:
	Card();
	Card(const MyString& description);
	virtual ~Card();

	virtual Card* clone() const = 0;

	virtual void printCardDescription() const = 0;
	virtual void applyEffect(Player& player) = 0;
};
