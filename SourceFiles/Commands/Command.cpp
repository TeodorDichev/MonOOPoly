#include "../../Headers/Commands/Command.h"

Command::Command()
{
	board = Board::getInstance();
	bank = Bank::getInstance();
}
