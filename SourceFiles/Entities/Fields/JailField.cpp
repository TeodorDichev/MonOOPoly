#include "../../../Headers/Entities/Fields/JailField.h"

void JailField::interactWithField(Player* player)
{
	if (player->getCurrentFieldIndex() == this->index)
	{
		std::cout << "You are in jail! You must pay 100$ to continue with your turn!" << std::endl;
	}
	else
	{
		player->setCurrentFieldIndex(this->index);
		std::cout << "You went to jail!" << std::endl;
	}
}
