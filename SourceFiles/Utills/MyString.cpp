#include "../../Headers/Utills/MyString.h"

MyString::MyString(size_t capacity)
{
	size = capacity - 1;
	data = new char[capacity];
}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
	MyString result(lhs.size + rhs.size + 1);

	result[0] = '\0';
	strcat(result.data, lhs.data);
	strcat(result.data, rhs.data);

	return result;
}

MyString& MyString::operator+=(const MyString& other)
{
	char* result = new char[(size += other.size) + 1];
	result[0] = '\0';
	strcat(result, data);
	strcat(result, other.data);

	delete[] data;
	data = result;

	return *this;
}

MyString& MyString::operator+=(const char* other)
{
	size_t len = strlen(other);
	char* result = new char[size + len + 1];

	result[0] = '\0';
	strcat(result, data);
	strcat(result, other);

	delete[] data;
	data = result;
	size += len;

	return *this;
}

MyString::MyString() : MyString(1)
{
	data[0] = '\0';
}

MyString::MyString(const char* data) : MyString(strlen(data) + 1)
{
	strcpy(this->data, data);
}

MyString::MyString(const MyString& other)
{
	copyFrom(other);
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}


void MyString::free()
{
	delete[] data;
	data = nullptr;
}

MyString::~MyString()
{
	free();
}

size_t MyString::length() const
{
	return size;
}

void MyString::copyFrom(const MyString& other)
{
	size = other.size;
	data = new char[size + 1];
	strcpy(data, other.data);
}

MyString::MyString(MyString&& other) noexcept
{
	data = other.data;
	other.data = nullptr;
	size = other.size;
}

MyString& MyString::operator=(MyString&& other) noexcept
{
	if (this != &other)
	{
		free();
		data = other.data;
		other.data = nullptr;
		size = other.size;
	}
	return *this;
}

char& MyString::operator[](size_t index)
{
	return data[index];
}

char MyString::operator[](size_t index) const
{
	return data[index];
}

MyString MyString::substr(size_t begin, size_t howMany) const
{
	if (begin + howMany > size)
		throw std::length_error("Error, Substr out of range");


	MyString res(howMany + 1);
	for (int i = 0; i < howMany; i++)
		res.data[i] = data[begin + i];
	res[howMany] = '\0';
	return res;
}

const char* MyString::c_str() const
{
	return data;
}

std::ostream& operator<<(std::ostream& os, const MyString& str)
{
	return os << str.c_str();
}

std::istream& operator>>(std::istream& is, MyString& str)
{
	char buff[1024];
	is >> buff;

	delete[] str.data;
	str.size = strlen(buff);
	str.data = new char[str.size + 1];
	strcpy(str.data, buff);
	return is;
}

bool operator<(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator<=(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}
bool operator>=(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}
bool operator>(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}
bool operator==(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}
bool operator!=(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) != 0;
}