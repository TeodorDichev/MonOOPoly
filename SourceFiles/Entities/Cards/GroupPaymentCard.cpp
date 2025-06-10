#include "../../../Headers/Entities/Cards/GroupPaymentCard.h"

GroupPaymentCard::GroupPaymentCard(int amount) : Card()
{
	this->amount = amount;
}

Card* GroupPaymentCard::clone() const
{
	return new GroupPaymentCard(*this);
}

void GroupPaymentCard::printCardDescription() const
{
	if (amount < 0)
	{
		std::cout << "You have to pay to every other player: " << (-1) * amount << "$" << std::endl;
	}
	else
	{
		std::cout << "You will receive from every other player: " << amount << "$" << std::endl;
	}
}

void GroupPaymentCard::applyEffect(Player& player) const
{
	Board* board = Board::getInstance();

	for (int i = 0; i < board->players.size(); i++)
	{
		if (board->players[i].getPlayerIndex() != player.getPlayerIndex() && !board->players[i].hasResigned())
		{
			if (amount < 0)
			{
				board->players[i].increaseBalance(amount * (-1));
				player.reduceBalance(amount * (-1));
			}
			else
			{
				board->players[i].reduceBalance(amount);
				player.increaseBalance(amount);
			}
		}
	}
}
