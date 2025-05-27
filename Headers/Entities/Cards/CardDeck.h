#pragma once
#include "Card.h"
#include "../../Utills/HeterogeneousStack.hpp"

class CardDeck
{
private:
	HeterogeneousStack<Card*> cards;

public:
	void shuffleCards();
	void putCardDown(Card* card);
	void drawCard(Player* player); // Other way is to return Card*
};
