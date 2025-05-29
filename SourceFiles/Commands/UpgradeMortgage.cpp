#include "../../Headers/Commands/UpgradeMortgage.h"

void UpgradeMortgage::execute() const
{
	if (board->getPlayerIndex() == -1)
	{
		throw new std::invalid_argument(ExceptionMessages::notStartedGame.c_str());
	}

}