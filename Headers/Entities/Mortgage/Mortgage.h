#pragma once

class Mortgage
{
public:
	virtual double getRentIncrease() const = 0;
	virtual ~Mortgage() = default;
};
