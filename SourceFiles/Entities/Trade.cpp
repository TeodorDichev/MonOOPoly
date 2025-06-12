#include "../../Headers/Entities/Trade.h"

int Trade::currIdIndex = 0;

Trade::Trade(int id, Player* sender, Player* receiver, const MyString& offerDescription, int propertyIndex, int requestedAmount, bool isAccepted)
	:Trade(sender, receiver, offerDescription, propertyIndex, requestedAmount)
{
	currIdIndex = (currIdIndex > id ? currIdIndex : id + 1);
	this->isAccepted = isAccepted;
}

Trade::Trade(Player* sender, Player* receiver, const MyString& offerDescription, int propertyIndex, int requestedAmount)
{
	id = currIdIndex++;
	this->sender = sender;
	this->receiver = receiver;
	this->offerDescription = offerDescription;
	this->propertyIndex = propertyIndex;
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
		<< " | description: " << offerDescription << " | " << " | property: " << propertyIndex
		<< " | status: " << (isAccepted ? "accepted":"rejected") << " | amount: " << requestedAmount << "$" << std::endl;
}

bool Trade::getOfferResponse() const
{
	return isAccepted;
}

int Trade::getPropertyIndex() const
{
	return propertyIndex;
}

int Trade::getRequestedAmount() const
{
	return requestedAmount;
}

void Trade::acceptOffer()
{
	isAccepted = true;
}

void Trade::saveToBin(std::ofstream& ofs) const
{
	int senderId = sender->getPlayerIndex();
	int receiverId = receiver->getPlayerIndex();
	ofs.write(reinterpret_cast<const char*>(&id), sizeof(id));
	ofs.write(reinterpret_cast<const char*>(&senderId), sizeof(senderId));
	ofs.write(reinterpret_cast<const char*>(&receiverId), sizeof(receiverId));
	ofs.write(reinterpret_cast<const char*>(&propertyIndex), sizeof(propertyIndex));
	ofs.write(reinterpret_cast<const char*>(&requestedAmount), sizeof(requestedAmount));
	ofs.write(reinterpret_cast<const char*>(&isAccepted), sizeof(isAccepted));

	FileFunctions::writeStringToBinFile(ofs, offerDescription);
}
