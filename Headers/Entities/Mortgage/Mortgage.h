#pragma once
#include "../Fields/Property.h"

class Mortgage
{
public:
	virtual double getRentIncrease() const = 0;
	virtual ~Mortgage() = default;
};
