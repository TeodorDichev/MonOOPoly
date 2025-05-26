#pragma once
#include "Field.h"
class GoToJailField : public Field
{
public:
	GoToJailField();
	GoToJailField(int index);

	void interactWithField(Player* player) override;
};
