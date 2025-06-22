#pragma once

#include <fstream>
#include "../../Utills/GlobalConstantsAndFunctions.h"

class Building
{
public:
	virtual double getRentIncrease() const = 0;
	virtual ~Building() = default;

	virtual Building* clone() const = 0;

	virtual bool isCastle() const = 0;
	virtual bool isCottage() const = 0;

	virtual void saveToBin(std::ofstream& ofs) const = 0;
};
