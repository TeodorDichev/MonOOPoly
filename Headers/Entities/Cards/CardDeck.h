#pragma once
#include "Card.h"
#include "../../Utills/HeterogeneousStack.hpp"

class CardDeck
{
private:
	HeterogeneousStack<Card*> cards;

public:
	void drawCard(Player* player); // Other way is to return Card*
};
