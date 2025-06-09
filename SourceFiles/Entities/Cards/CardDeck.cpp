#include "../../../Headers/Entities/Cards/CardDeck.h"

void CardDeck::drawCard(Player* player)
{
	std::srand(std::time(nullptr));

	int index = std::rand() % cards.getSize() + 1;

	cards[index]->applyEffect(*player);
	cards[index]->printCardDescription();
}
