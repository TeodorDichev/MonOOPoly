#include "../../../Headers/Entities/Mortgage/Castle.h"

double Castle::getRentIncrease() const
{
	return this->rentIncreasePercentage;
}

bool Castle::isCastle() const
{
	return true;
}

bool Castle::isCottage() const
{
	return false;
}

Mortgage* Castle::clone() const
{
	return new Castle(*this);
}
