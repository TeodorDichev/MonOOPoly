#include "../../Headers/Commands/CheckField.h"

void CheckField::execute() const
{
	if (board->getPlayerIndex() == -1)
	{
		throw new std::invalid_argument(ExceptionMessages::notStartedGame.c_str());
	}

}