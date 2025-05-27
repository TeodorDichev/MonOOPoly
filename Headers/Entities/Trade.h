#pragma once
#include "Player.h"

class Trade
{
private:
	Player* player1;
	Player* player2;
	MyString offerDescription;
	Property* property;
	int requestedAmount;
	bool isAccepted;

public:
	Trade();
	Trade(Player* player1, Player* player2,	const MyString& offerDescription, Property* property, int requestedAmount);

	void printOffer();
	void acceptOffer(); // removes sum/prop from p1 and gives sum/prop to p2
	void rejectOffer();
	void getOfferResponce();
};
