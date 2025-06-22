#pragma once
#include "Building.h"

class Cottage : public Building
{
private:
	const double rentIncreasePercentage = 1.15;

public:
	double getRentIncrease() const override;
	bool isCastle() const override;
	bool isCottage() const override;
	Building* clone() const override;
	void saveToBin(std::ofstream& ofs) const override;
};
