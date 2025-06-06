#include "../../../Headers/Entities/Fields/Property.h"

void Property::interactWithField(Player* player)
{
	player->visit(this);	
}

void Property::payRent() const
{
	owner->addToBalance(getRent());
}
