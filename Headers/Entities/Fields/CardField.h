#pragma once
#include "Field.h"
#include "../Cards/CardDeck.h"


class CardField : public Field
{
private:
	// All card field have a pointer to the single card deck
	CardDeck* deck;

public:
	CardField();
	CardField(int index, const MyString& description);

	void interactWithField(Player* player) override;
	void printInfo() const override;
};
