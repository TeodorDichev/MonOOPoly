#include "../../../Headers/Entities/Cards/PaymentCard.h"

PaymentCard::PaymentCard(int amount) : Card()
{
	this->amount = amount;
}

Card* PaymentCard::clone() const
{
	return new PaymentCard(*this);
}

void PaymentCard::printCardDescription() const
{
	if (amount < 0)
	{
		std::cout << "You have to pay " << (-1) * amount << "$" << std::endl;
	}
	else
	{
		std::cout << "You will receive " << amount << " $" << std::endl;
	}
}

void PaymentCard::applyEffect(Player& player) const
{
	player.addToBalance(amount);
}