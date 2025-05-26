#pragma once
#include "Command.h"

class UpgradeMortgage : public Command
{
public:
    UpgradeMortgage() = default;
    virtual void execute() const override;
};
