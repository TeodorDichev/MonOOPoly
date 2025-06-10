#include "../../Headers/Entities/Trade.h"

int Trade::currIdIndex = 0;


Trade::Trade(int id, Player* sender, Player* receiver, const MyString& offerDescription, Property* property, int requestedAmount)
{
	currIdIndex = (currIdIndex > id ? currIdIndex : id + 1);
}

Trade::Trade(Player* sender, Player* receiver, const MyString& offerDescription, Property* property, int requestedAmount)
{
	id = currIdIndex++;
	this->sender = sender;
	this->receiver = receiver;
	this->offerDescription = offerDescription;
	this->property = property;
	this->requestedAmount = requestedAmount;
}

int Trade::getTradeId() const
{
	return id;
}

int Trade::getSenderIndex() const
{
	return sender->getPlayerIndex();
}

int Trade::getReceiverIndex() const
{
	return receiver->getPlayerIndex();
}

void Trade::printOffer() const
{
	std::cout << "id: " << id  << " | sender: " << sender->getName() << " | receiver: " << receiver->getName()
		<< " | description: " << offerDescription << " | " << " | property: " << property->getFieldIndex()
		<< " | status: " << (isAccepted ? "accepted":"rejected") << " | amount: " << requestedAmount << "$" << std::endl;
}

bool Trade::getOfferResponse() const
{
	return isAccepted;
}

void Trade::acceptOffer()
{
	if (sender->owsProperty(property->getFieldIndex()))
	{
		// Then the sender sells the property
		if (!receiver->hasSufficientFund(requestedAmount))
		{
			throw std::invalid_argument(ExceptionMessages::insufficientFunds.c_str());
		}

		property->removeOwner();
		sender->addToBalance(requestedAmount);

		property->setOwner(receiver);
		receiver->addToBalance((-1) * requestedAmount);
		isAccepted = true;
	}
	else if (receiver->owsProperty(property->getFieldIndex()))
	{
		// Then the sender buys the property
		if (!sender->hasSufficientFund(requestedAmount))
		{
			throw std::invalid_argument(ExceptionMessages::insufficientFunds.c_str());
		}

		property->removeOwner();
		receiver->addToBalance(requestedAmount);

		property->setOwner(sender);
		sender->addToBalance((-1) * requestedAmount);
		isAccepted = true;
	}
	else
	{
		throw std::invalid_argument(ExceptionMessages::invalidFieldIndex.c_str());
	}
}
