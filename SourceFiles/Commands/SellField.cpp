#include "../../Headers/Commands/SellField.h"

void SellField::execute() const
{
	if (board->getPlayerIndex() == -1)
	{
		throw new std::invalid_argument(ExceptionMessages::notStartedGame.c_str());
	}

}