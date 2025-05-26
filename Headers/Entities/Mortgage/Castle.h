#pragma once
#include "Mortgage.h"

class Castle : public Mortgage
{
private:
	const double rentIncreasePercentage = 1.5;

public:
	double getRentIncrease() const override;
};
