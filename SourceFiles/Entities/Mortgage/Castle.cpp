#include "../../../Headers/Entities/Mortgage/Castle.h"

double Castle::getRentIncrease() const
{
	return this->rentIncreasePercentage;
}

bool Cottage::isCastle() const
{
	return true;
}

bool Cottage::isCottage() const
{
	return false;
}

Mortgage* Castle::clone() const
{
	return new Castle(*this);
}
