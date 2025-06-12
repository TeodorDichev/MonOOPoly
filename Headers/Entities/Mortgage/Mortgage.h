#pragma once

#include <fstream>
#include "../../Utills/GlobalConstantsAndFunctions.h"

class Mortgage
{
public:
	virtual double getRentIncrease() const = 0;
	virtual ~Mortgage() = default;

	virtual Mortgage* clone() const = 0;

	virtual bool isCastle() const = 0;
	virtual bool isCottage() const = 0;

	virtual void saveToBin(std::ofstream& ofs) const = 0;
};
