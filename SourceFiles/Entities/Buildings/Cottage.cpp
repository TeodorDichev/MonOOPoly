#include "../../../Headers/Entities/Buildings/Cottage.h"

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

Building* Cottage::clone() const
{
	return new Cottage(*this);
}

void Cottage::saveToBin(std::ofstream& ofs) const
{
	int type = (int)MortgageType::cottage;
	ofs.write(reinterpret_cast<const char*>(&type), sizeof(type));
}
