#pragma once
#include "Player.h"

class Trade
{
private:
	static int currIdIndex;

	int id = -1;
	Player* sender = nullptr;
	Player* receiver = nullptr;
	MyString offerDescription;
	int propertyIndex = -1;
	int requestedAmount = 0;
	bool isAccepted = false;

public:
	Trade() = default;
	Trade(Player* sender, Player* receiver,	const MyString& offerDescription, int propertyIndex, int requestedAmount);
	Trade(int id, Player* sender, Player* receiver,	const MyString& offerDescription, int propertyIndex, int requestedAmount, bool isAccepted);

	int getTradeId() const;
	int getSenderIndex() const;
	int getReceiverIndex() const;
	bool getOfferResponse() const;
	int getPropertyIndex() const;
	int getRequestedAmount() const;

	void printOffer() const;
	void acceptOffer();
	void saveToBin(std::ofstream& ofs) const;
};
