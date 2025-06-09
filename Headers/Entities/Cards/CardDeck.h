#pragma once
#include "Card.h"
#include "../../Utills/HeterogeneousContainer.hpp"

class CardDeck
{
private:
	HeterogeneousContainer<Card> cards;

public:
	void drawCard(Player* player);
};
