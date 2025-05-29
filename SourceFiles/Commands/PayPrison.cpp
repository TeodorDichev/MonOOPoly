#include "../../Headers/Commands/PayPrison.h"

void PayPrison::execute() const
{
	if (board->getPlayerIndex() == -1)
	{
		throw new std::invalid_argument(ExceptionMessages::notStartedGame.c_str());
	}
}