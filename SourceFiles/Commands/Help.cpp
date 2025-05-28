#include "../../Headers/Commands/Help.h"

void Help::execute() const
{
	SerializeFunctions::printRules();
}