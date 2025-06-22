#pragma once
#include "Command.h"

class UpgradeBuilding : public Command
{
public:
    UpgradeBuilding() = default;
    virtual void execute() const override;
};
