#pragma once
#include "Player.h"

class Trade
{
private:
	static int currIdIndex;

	int id;
	Player* sender;
	Player* receiver;
	MyString offerDescription;
	Property* property;
	int requestedAmount;
	bool isAccepted = false;

public:
	Trade() = default;
	Trade(Player* sender, Player* receiver,	const MyString& offerDescription, Property* property, int requestedAmount);
	Trade(int id, Player* sender, Player* receiver,	const MyString& offerDescription, Property* property, int requestedAmount);

	int getTradeId() const;
	int getSenderIndex() const;
	int getReceiverIndex() const;
	bool getOfferResponse() const;

	void printOffer() const;
	void acceptOffer();
};
