#include "../../../Headers/Entities/Mortgage/Cottage.h"

double Cottage::getRentIncrease() const
{
	return this->rentIncreasePercentage;
}

bool Cottage::isCastle() const
{
	return false;
}

bool Cottage::isCottage() const
{
	return true;
}

Mortgage* Cottage::clone() const
{
	return new Cottage(*this);
}