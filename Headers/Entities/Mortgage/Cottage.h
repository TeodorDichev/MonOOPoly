#pragma once
#include "Mortgage.h"

class Cottage : public Mortgage
{
private:
	const double rentIncreasePercentage = 1.15;

public:
	double getRentIncrease() const override;
	bool isCastle() const override;
	bool isCottage() const override;
	Mortgage* clone() const override;
};
