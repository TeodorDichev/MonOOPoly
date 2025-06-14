#include "../../Headers/Utills/SerializeFunctions.h"
#include "../../Headers/Entities/Fields/Property.h"
#include "../../Headers/Entities/Fields/StartField.h"
#include "../../Headers/Entities/Fields/FreeParkingField.h"
#include "../../Headers/Entities/Fields/GoToJailField.h"
#include "../../Headers/Entities/Fields/JailField.h"
#include "../../Headers/Entities/Fields/CardField.h"

#include "../../Headers/Entities/Cards/GroupPaymentCard.h"
#include "../../Headers/Entities/Cards/PaymentCard.h"
#include "../../Headers/Entities/Cards/MovePositionCard.h"

static size_t getFileSize(std::ifstream& ifs)
{
	size_t currPos = ifs.tellg();
	ifs.seekg(0, std::ios::end);
	size_t size = ifs.tellg();
	ifs.seekg(currPos, std::ios::beg);
	return size;
}

Board* SerializeFunctions::board = Board::getInstance();
Bank* SerializeFunctions::bank = Bank::getInstance();

void SerializeFunctions::saveGameToFile()
{
	std::ofstream fieldsStream(GlobalConstants::prevGameFieldsFile.c_str(), std::ios::binary | std::ios::trunc);
	std::ofstream playersStream(GlobalConstants::prevGamePlayersFile.c_str(), std::ios::binary | std::ios::trunc);
	std::ofstream tradesStream(GlobalConstants::prevGameTradesFile.c_str(), std::ios::binary | std::ios::trunc);

	if (!fieldsStream.is_open() || !playersStream.is_open() || !tradesStream.is_open())
	{
		throw std::invalid_argument(ExceptionMessages::failedToOpenFile.c_str());
	}

	int fieldsCount = board->getBoardSize();
	fieldsStream.write(reinterpret_cast<const char*>(&fieldsCount), sizeof(fieldsCount));

	for (int i = 0; i < board->fields.getSize(); i++)
	{
		board->fields[i]->saveToBin(fieldsStream);
	}

	int currentPlayerIndex = board->getCurrentPlayerIndex();
	playersStream.write(reinterpret_cast<const char*>(&currentPlayerIndex), sizeof(currentPlayerIndex));

	int playersCount = board->players.size();
	playersStream.write(reinterpret_cast<const char*>(&playersCount), sizeof(playersCount));

	for (int i = 0; i < playersCount; ++i)
	{
		board->players[i].saveToBin(playersStream);
	}

	int tradesCount = bank->trades.size();
	tradesStream.write(reinterpret_cast<const char*>(&tradesCount), sizeof(tradesCount));

	for (int i = 0; i < tradesCount; ++i)
	{
		bank->trades[i].saveToBin(tradesStream);
	}
}

void SerializeFunctions::loadGameFromFile()
{
	std::ifstream cardsStream(GlobalConstants::cardsFileName.c_str());

	if (!cardsStream.is_open())
	{
		throw std::invalid_argument(ExceptionMessages::failedToOpenFile.c_str());
	}

	loadCardsTxt(cardsStream);

	std::ifstream playersStream(GlobalConstants::prevGamePlayersFile.c_str(), std::ios::binary);
	std::ifstream fieldsStream(GlobalConstants::prevGameFieldsFile.c_str(), std::ios::binary);
	std::ifstream tradesStream(GlobalConstants::prevGameTradesFile.c_str(), std::ios::binary);

	if (!fieldsStream.is_open() || !playersStream.is_open() || !tradesStream.is_open())
	{
		throw std::invalid_argument(ExceptionMessages::noPrevGames.c_str());
	}

	int currentPlayerIndex;
	playersStream.read(reinterpret_cast<char*>(&currentPlayerIndex), sizeof(currentPlayerIndex));
	board->currPlayerIndex = currentPlayerIndex;;

	loadPlayersBin(playersStream);
	loadFieldsBin(fieldsStream);
	loadTradesBin(tradesStream);
}

void SerializeFunctions::startNewGame()
{
	std::ifstream cardsStream(GlobalConstants::cardsFileName.c_str());
	std::ifstream fieldsStream(GlobalConstants::fieldsFileName.c_str());

	if (!cardsStream.is_open() || !fieldsStream.is_open())
	{
		throw std::invalid_argument(ExceptionMessages::failedToOpenFile.c_str());
	}

	loadCardsTxt(cardsStream);
	loadFieldsTxt(fieldsStream);
}

void SerializeFunctions::printHelp()
{
	std::ifstream ifs("Help.txt");

	if (!ifs.is_open())
	{
		throw std::invalid_argument("Failed to open Help.txt");
	}

	char ch;
	while (ifs.get(ch))
	{
		std::cout << ch;
	}

	ifs.close();
}

void SerializeFunctions::loadFieldsTxt(std::ifstream& ifs)
{
	int type;

	while (ifs >> type)
	{
		int index;
		MyString content;

		ifs >> index >> content;

		switch (type)
		{
		case (int)FieldType::start:
			board->fields.addObject(new StartField(index, content));
			break;

		case (int)FieldType::property:
		{
			MyString color;
			int rent, purchase, cottage, castle;
			ifs >> color >> rent >> purchase >> cottage >> castle;
			board->fields.addObject(new Property(index, content, color, rent, purchase, cottage, castle));
			break;
		}

		case (int)FieldType::card:
			board->fields.addObject(new CardField(index, content, &board->cardDeck));
			break;

		case (int)FieldType::jail:
		{
			int tax;
			ifs >> tax;
			board->fields.addObject(new JailField(index, content, tax));
			break;
		}

		case (int)FieldType::goToJail:
		{
			int jailIndex;
			ifs >> jailIndex;
			board->fields.addObject(new GoToJailField(index, content, jailIndex));
			break;
		}

		case (int)FieldType::freeParking:
			board->fields.addObject(new FreeParkingField(index, content));
			break;

		default:
			throw std::invalid_argument(ExceptionMessages::unknownFieldType.c_str());
			break;
		}
	}
}

void SerializeFunctions::loadFieldsBin(std::ifstream& ifs)
{
	int fieldsCount = 0;
	ifs.read(reinterpret_cast<char*>(&fieldsCount), sizeof(fieldsCount));

	for (int i = 0; i < fieldsCount; i++)
	{
		int type;
		ifs.read(reinterpret_cast<char*>(&type), sizeof(type));

		int index;
		ifs.read(reinterpret_cast<char*>(&index), sizeof(index));

		MyString content = FileFunctions::readStringFromBinFile(ifs);

		switch (type)
		{
		case (int)FieldType::start:
			board->fields.addObject(StartField(index, content));
			break;
		case (int)FieldType::property:
		{
			MyString color = FileFunctions::readStringFromBinFile(ifs);
			int rent, purchase, cottage, castle;
			ifs.read(reinterpret_cast<char*>(&rent), sizeof(rent));
			ifs.read(reinterpret_cast<char*>(&purchase), sizeof(purchase));
			ifs.read(reinterpret_cast<char*>(&cottage), sizeof(cottage));
			ifs.read(reinterpret_cast<char*>(&castle), sizeof(castle));

			Property* property = new Property(index, content, color, rent, purchase, cottage, castle);

			int ownerIndex;
			ifs.read(reinterpret_cast<char*>(&ownerIndex), sizeof(ownerIndex));

			Player* player = board->getPlayer(ownerIndex);
			if (player != nullptr)
			{
				property->setOwner(player);
				player->addProperty(property);
			}

			bool isMortgaged;
			ifs.read(reinterpret_cast<char*>(&isMortgaged), sizeof(isMortgaged));

			if (isMortgaged)
			{
				int mortgageType;
				ifs.read(reinterpret_cast<char*>(&mortgageType), sizeof(mortgageType));

				switch (mortgageType)
				{
				case (int)MortgageType::cottage:
					property->addMortgage(Cottage());
					break;
				case (int)MortgageType::castle:
					property->addMortgage(Castle());
					break;
				default:
					break;
				}
			}

			board->fields.addObject(property);

			// I do not delete the property because now board is responsible for its lifespan and it will delete it when we free the last instance of board
			// my heterogeneous container attaches the pointer and deletes the object and the pointer at the end of its life span so there are no memory leaks

			break;
		}
		case (int)FieldType::card:
			board->fields.addObject(CardField(index, content, &board->cardDeck));
			break;
		case (int)FieldType::jail:
		{
			int tax;
			ifs.read(reinterpret_cast<char*>(&tax), sizeof(tax));

			board->fields.addObject(JailField(index, content, tax));
			break;
		}
		case (int)FieldType::goToJail:
		{
			int jailIndex;
			ifs.read(reinterpret_cast<char*>(&jailIndex), sizeof(jailIndex));

			board->fields.addObject(GoToJailField(index, content, jailIndex));
			break;
		}
		case (int)FieldType::freeParking:
			board->fields.addObject(FreeParkingField(index, content));
			break;
		default:
			throw std::invalid_argument(ExceptionMessages::unknownFieldType.c_str());
			break;
		}
	}
}

void SerializeFunctions::loadPlayersBin(std::ifstream& ifs)
{
	int playersCount = 0;
	ifs.read(reinterpret_cast<char*>(&playersCount), sizeof(playersCount));

	for (int i = 0; i < playersCount; i++)
	{
		bool resigned, skipTurn;
		int balance, pairsCount, playerIndex, currentFieldIndex;

		ifs.read(reinterpret_cast<char*>(&resigned), sizeof(resigned));
		ifs.read(reinterpret_cast<char*>(&skipTurn), sizeof(skipTurn));
		ifs.read(reinterpret_cast<char*>(&balance), sizeof(balance));
		ifs.read(reinterpret_cast<char*>(&pairsCount), sizeof(pairsCount));
		ifs.read(reinterpret_cast<char*>(&playerIndex), sizeof(playerIndex));
		ifs.read(reinterpret_cast<char*>(&currentFieldIndex), sizeof(currentFieldIndex));

		MyString playerName = FileFunctions::readStringFromBinFile(ifs);
		MyString color = FileFunctions::readStringFromBinFile(ifs);

		board->addPlayer(Player(playerIndex, playerName, color, balance, resigned, skipTurn, pairsCount, currentFieldIndex));
	}
}

void SerializeFunctions::loadTradesBin(std::ifstream& ifs)
{
	int tradesCount = 0;
	ifs.read(reinterpret_cast<char*>(&tradesCount), sizeof(tradesCount));

	for (int i = 0; i < tradesCount; i++)
	{
		int id, senderId, receiverId, propertyIndex, requestedAmount;
		bool isAccepted;

		ifs.read(reinterpret_cast<char*>(&id), sizeof(id));
		ifs.read(reinterpret_cast<char*>(&senderId), sizeof(senderId));
		ifs.read(reinterpret_cast<char*>(&receiverId), sizeof(receiverId));
		ifs.read(reinterpret_cast<char*>(&propertyIndex), sizeof(propertyIndex));
		ifs.read(reinterpret_cast<char*>(&requestedAmount), sizeof(requestedAmount));
		ifs.read(reinterpret_cast<char*>(&isAccepted), sizeof(isAccepted));

		MyString offerDescription = FileFunctions::readStringFromBinFile(ifs);

		bank->addTrade(Trade(id, board->getPlayer(senderId), board->getPlayer(receiverId), offerDescription, propertyIndex, requestedAmount, isAccepted));
	}
}

void SerializeFunctions::loadCardsTxt(std::ifstream& ifs)
{
	int typeValue;

	while (ifs >> typeValue)
	{
		int value;
		ifs >> value;

		switch (typeValue)
		{
		case (int)CardType::move:
			board->cardDeck.addCard(MovePositionCard(value));
			break;
		case (int)CardType::payment:
			board->cardDeck.addCard(PaymentCard(value));
			break;
		case (int)CardType::groupPayment:
			board->cardDeck.addCard(GroupPaymentCard(value));
			break;
		default:
			throw std::invalid_argument(ExceptionMessages::unknownCardType.c_str());
			break;
		}
	}
}
