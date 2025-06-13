#include "../../../Headers/Entities/Cards/CardDeck.h"

void CardDeck::drawCard(Player* player) const
{
	std::srand(std::time(nullptr));

	int index = std::rand() % cards.getSize();

	cards[index]->printCardDescription();
	cards[index]->applyEffect(*player);
}

void CardDeck::addCard(const Card& card)
{
	cards.addObject(card);
}
