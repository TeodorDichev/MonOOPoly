#include "../../../Headers/Entities/Buildings/Castle.h"

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

Building* Castle::clone() const
{
	return new Castle(*this);
}

void Castle::saveToBin(std::ofstream& ofs) const
{
	int type = (int)MortgageType::castle;
	ofs.write(reinterpret_cast<const char*>(&type), sizeof(type));
}
