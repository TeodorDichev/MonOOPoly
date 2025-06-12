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

void SerializeFunctions::saveGameToFile()
{
	std::ofstream fieldsStream(GlobalConstants::prevGameFields.c_str(), std::ios::binary | std::ios::trunc);
	if (!fieldsStream.is_open())
	{
		throw std::invalid_argument(ExceptionMessages::failedToOpenFile.c_str());
	}

	int fieldsCount = board->getBoardSize();
	fieldsStream.write(reinterpret_cast<const char*>(&fieldsCount), sizeof(fieldsCount));

	for (int i = 0; i < board->fields.getSize(); i++)
	{
		board->fields[i]->saveToBin(fieldsStream);
	}

	std::ofstream playersStream(GlobalConstants::prevGamePlayers.c_str(), std::ios::binary | std::ios::trunc);

	if (!playersStream.is_open())
	{
		throw std::invalid_argument(ExceptionMessages::failedToOpenFile.c_str());
	}

	int currentPlayerIndex = board->getCurrentPlayerIndex();
	playersStream.write(reinterpret_cast<const char*>(&currentPlayerIndex), sizeof(currentPlayerIndex));

	int playersCount = board->players.size();
	playersStream.write(reinterpret_cast<const char*>(&playersCount), sizeof(playersCount));

	for (int i = 0; i < playersCount; ++i)
	{
		board->players[i].saveToBin(playersStream);
	}
}

void SerializeFunctions::loadGameFromFile()
{
	// Cards
	std::ifstream cardsStream(GlobalConstants::cardsFileName.c_str());

	if (!cardsStream.is_open())
	{
		throw std::invalid_argument(ExceptionMessages::failedToOpenFile.c_str());
	}

	loadCardsTxt(cardsStream);

	// Players
	std::ifstream playersStream(GlobalConstants::prevGamePlayers.c_str(), std::ios::binary);
	if (!playersStream.is_open())
	{
		std::ofstream ofs("Players.dat", std::ios::binary);
		ofs.close();
		return;
	}

	if (getFileSize(playersStream) == 0)
	{
		throw std::invalid_argument(ExceptionMessages::noPrevGames.c_str());
	}

	int currentPlayerIndex;
	playersStream.read(reinterpret_cast<char*>(&currentPlayerIndex), sizeof(currentPlayerIndex));
	board->setPlayerIndex(currentPlayerIndex);

	loadPlayersBin(playersStream);

	//  Fields
	std::ifstream fieldsStream(GlobalConstants::prevGameFields.c_str(), std::ios::binary);
	if (!fieldsStream.is_open())
	{
		std::ofstream ofs("Fields.dat", std::ios::binary);
		ofs.close();
		return;
	}

	if (getFileSize(fieldsStream) == 0)
	{
		throw std::invalid_argument(ExceptionMessages::noPrevGames.c_str());
	}

	loadFieldsBin(fieldsStream);

}

void SerializeFunctions::startNewGame()
{
	std::ifstream cardsStream(GlobalConstants::cardsFileName.c_str());

	if (!cardsStream.is_open())
	{
		throw std::invalid_argument(ExceptionMessages::failedToOpenFile.c_str());
	}

	loadCardsTxt(cardsStream);
	
	std::ifstream fieldsStream(GlobalConstants::fieldsFileName.c_str());

	if (!fieldsStream.is_open())
	{
		throw std::invalid_argument(ExceptionMessages::failedToOpenFile.c_str());
	}
	
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

void SerializeFunctions::loadFieldsTxt(std::ifstream& fieldsStream)
{
	MyString type;

	while (fieldsStream >> type)
	{
		int index;
		MyString content;

		fieldsStream >> index >> content;

		if (type == "Start")
		{
			board->fields.addObject(new StartField(index, content));
		}
		else if (type == "Property")
		{
			MyString color;
			int rent, purchase, cottage, castle;
			fieldsStream >> color >> rent >> purchase >> cottage >> castle;

			board->fields.addObject(new Property(index, content, color, rent, purchase, cottage, castle));
		}
		else if (type == "Cards")
		{
			board->fields.addObject(new CardField(index, content, &board->cardDeck));
		}
		else if (type == "Jail")
		{
			int tax;
			fieldsStream >> tax;

			board->fields.addObject(new JailField(index, content, tax));
		}
		else if (type == "GoJail")
		{
			int jailIndex;
			fieldsStream >> jailIndex;

			board->fields.addObject(new GoToJailField(index, content, jailIndex));
		}
		else if (type == "Park")
		{
			board->fields.addObject(new FreeParkingField(index, content));
		}
		else
		{
			throw std::invalid_argument(ExceptionMessages::unknownFieldType.c_str());
		}
	}
}

void SerializeFunctions::loadFieldsBin(std::ifstream& fieldsStream)
{
	int fieldsCount = 0;
	fieldsStream.read(reinterpret_cast<char*>(&fieldsCount), sizeof(fieldsCount));

	for (int i = 0; i < fieldsCount; i++)
	{
		MyString type = FileFunctions::readStringFromBinFile(fieldsStream);

		int index;
		fieldsStream.read(reinterpret_cast<char*>(&index), sizeof(index));

		MyString content = FileFunctions::readStringFromBinFile(fieldsStream);

		if (type == "Start")
		{
			board->fields.addObject(new StartField(index, content));
		}
		else if (type == "Property")
		{
			MyString color = FileFunctions::readStringFromBinFile(fieldsStream);

			int rent, purchase, cottage, castle;
			fieldsStream.read(reinterpret_cast<char*>(&rent), sizeof(rent));
			fieldsStream.read(reinterpret_cast<char*>(&purchase), sizeof(purchase));
			fieldsStream.read(reinterpret_cast<char*>(&cottage), sizeof(cottage));
			fieldsStream.read(reinterpret_cast<char*>(&castle), sizeof(castle));

			Property* property = new Property(index, content, color, rent, purchase, cottage, castle);

			int ownerIndex;
			fieldsStream.read(reinterpret_cast<char*>(&ownerIndex), sizeof(ownerIndex));

			Player* player = board->getPlayer(ownerIndex);
			if (player != nullptr)
			{
				property->setOwner(player);
			}

			int isMortgaged;
			fieldsStream.read(reinterpret_cast<char*>(&isMortgaged), sizeof(isMortgaged));

			if (isMortgaged == 1)
			{
				MyString mortgage = FileFunctions::readStringFromBinFile(fieldsStream);
				if (mortgage == "Castle")
				{
					property->addMortgage(new Castle());
				}
				else if (mortgage == "Cottage")
				{
					property->addMortgage(new Cottage());
				}
			}

			player->addProperty(property);
			board->fields.addObject(property);
			delete property;
		}
		else if (type == "Cards")
		{
			board->fields.addObject(new CardField(index, content, &board->cardDeck));
		}
		else if (type == "Jail")
		{
			int tax;
			fieldsStream.read(reinterpret_cast<char*>(&tax), sizeof(tax));

			board->fields.addObject(new JailField(index, content, tax));
		}
		else if (type == "GoJail")
		{
			int jailIndex;
			fieldsStream.read(reinterpret_cast<char*>(&jailIndex), sizeof(jailIndex));

			board->fields.addObject(new GoToJailField(index, content, jailIndex));
		}
		else if (type == "Park")
		{
			board->fields.addObject(new FreeParkingField(index, content));
		}
		else
		{
			throw std::invalid_argument(ExceptionMessages::unknownFieldType.c_str());
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

		board->addPlayer(Player(playerIndex, playerName, balance, resigned, skipTurn, pairsCount, currentFieldIndex));
	}
}

void SerializeFunctions::loadCardsTxt(std::ifstream& cardsStream)
{
	MyString type;

	while (cardsStream >> type)
	{
		int value;
		cardsStream >> value;

		if (type == "Move")
		{
			board->cardDeck.addCard(MovePositionCard(value));
		}
		else if (type == "Group")
		{
			board->cardDeck.addCard(GroupPaymentCard(value));
		}
		else if (type == "Pay")
		{
			board->cardDeck.addCard(PaymentCard(value));
		}
		else
		{
			throw std::invalid_argument(ExceptionMessages::unknownCardType.c_str());
		}
	}
}
