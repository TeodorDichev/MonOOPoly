#include "../../Headers/Utills/SerializeFunctions.h"

#include<fstream>

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
	while (fieldsStream.peek() != fieldsStream.eof())
	{
		MyString type = readStringFromBinFile(fieldsStream);

		int index;
		fieldsStream.read(reinterpret_cast<char*>(&index), sizeof(index));

		MyString content = readStringFromBinFile(fieldsStream);

		if (type == "Start")
		{
			board->fields.addObject(new StartField(index, content));
		}
		else if (type == "Property")
		{
			MyString color = readStringFromBinFile(fieldsStream);

			int rent, purchase, cottage, castle;
			fieldsStream.read(reinterpret_cast<char*>(&rent), sizeof(rent));
			fieldsStream.read(reinterpret_cast<char*>(&purchase), sizeof(purchase));
			fieldsStream.read(reinterpret_cast<char*>(&cottage), sizeof(cottage));
			fieldsStream.read(reinterpret_cast<char*>(&castle), sizeof(castle));

			int ownerIndex;
			fieldsStream.read(reinterpret_cast<char*>(&ownerIndex), sizeof(ownerIndex));

			Player* player = board->getPlayer(ownerIndex);
			if (player)
			{
				player.
			}

			int isMortgaged;
			fieldsStream.read(reinterpret_cast<char*>(&isMortgaged), sizeof(isMortgaged));

			Property* property = new Property(index, content, color, rent, purchase, cottage, castle);

			if (isMortgaged == 1)
			{
				MyString mortgage = readStringFromBinFile(fieldsStream);
				if (mortgage == "Castle")
				{
					property->addMortgage(new Castle());
				}
				else if (mortgage == "Cottage")
				{
					property->addMortgage(new Cottage());
				}
			}

			board->fields.addObject(new Property(index, content, color, rent, purchase, cottage, castle));
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

		MyString playerName = readStringFromBinFile(ifs);

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

void SerializeFunctions::writeStringToBinFile(std::ofstream& ofs, const MyString& str)
{
	int len = str.length();
	ofs.write((const char*)&len, sizeof(int));
	ofs.write(str.c_str(), sizeof(char) * len);
}

MyString SerializeFunctions::readStringFromBinFile(std::ifstream& ifs)
{
	int len = 0;
	ifs.read((char*)&len, sizeof(len));

	char* buff = new char[len + 1];
	ifs.read(buff, sizeof(char) * len);

	buff[len] = '\0';

	MyString toReturn(buff);

	delete[] buff;

	return toReturn;
}