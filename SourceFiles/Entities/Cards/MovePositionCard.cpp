#include "../../../Headers/Entities/Cards/MovePositionCard.h"

MovePositionCard::MovePositionCard(int positions) : Card()
{
	this->positions = positions;
}

Card* MovePositionCard::clone() const
{
	return new MovePositionCard(*this);
}

void MovePositionCard::printCardDescription() const
{
	if (positions < 0)
	{
		std::cout << "You have to move " << (-1) * positions << " backwards" << std::endl;
	}
	else
	{
		std::cout << "You have to move " << positions << " forward" << "$" << std::endl;
	}
}

void MovePositionCard::applyEffect(Player& player) const
{
	player.moveWith(positions);

	Board* board = Board::getInstance();
	board->getField(player.getCurrentFieldIndex())->interactWithField(&player);
}