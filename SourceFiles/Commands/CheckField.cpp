#include "../../Headers/Commands/CheckField.h"

void CheckField::execute() const
{
	int fieldIndex;
	std::cin >> fieldIndex;
	
	if (board->getPlayerIndex() == -1)
	{
		throw new std::invalid_argument(ExceptionMessages::notStartedGame.c_str());
	}
	if (fieldIndex < 0 || fieldIndex >= GlobalFunctionsAndConstants::boardSize)
	{
		throw new std::invalid_argument(ExceptionMessages::invalidFieldIndex.c_str());
	}

	board->getField(fieldIndex)->printInfo();
}