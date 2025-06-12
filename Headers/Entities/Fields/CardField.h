#pragma once
#include "Field.h"
#include "../Cards/CardDeck.h"


class CardField : public Field
{
private:
	// All card field have a pointer to the a card deck
	const CardDeck* deck = nullptr;

public:
	CardField();
	CardField(int index, const MyString& content, const CardDeck* ptr);
	Field* clone() const override;

	void interactWithField(Player* player) override;
	void printInfo() const override;

	bool isJail() const override;
	void saveToBin(std::ofstream& ofs) const override;
};
