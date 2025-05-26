#pragma once

#include <iostream>
#include <utility>

template <typename T>
class HeterogeneousStack
{
private:
	T** data;
	size_t size;
	size_t capacity;

	void resize(size_t newCapacity);

	unsigned int getNextPowerOfTwo(unsigned int n) const;
	unsigned int allocateCapacity(unsigned int n) const;

	void copyFrom(const HeterogeneousStack& other);
	void moveFrom(HeterogeneousStack&& other) noexcept;
	void free() noexcept;

public:
	HeterogeneousStack();
	explicit HeterogeneousStack(size_t N);

	HeterogeneousStack(const HeterogeneousStack& other);
	HeterogeneousStack& operator=(const HeterogeneousStack& other);

	HeterogeneousStack(HeterogeneousStack&& other) noexcept;
	HeterogeneousStack& operator=(HeterogeneousStack&& other) noexcept;

	size_t getSize() const;
	size_t getCapacity() const;

	HeterogeneousStack& push(const T& elem);
	HeterogeneousStack& push(T&& elem);

	HeterogeneousStack& pop();

	const T& top() const;

	~HeterogeneousStack() noexcept;
};

template<typename T>
inline HeterogeneousStack<T>::HeterogeneousStack() : HeterogeneousStack(4)
{ }

template<typename T>
inline HeterogeneousStack<T>::HeterogeneousStack(size_t N) : size(0)
{
	this->capacity = allocateCapacity(N);
	this->data = new T[this->capacity]{ };
}

template<typename T>
inline HeterogeneousStack<T>::HeterogeneousStack(const HeterogeneousStack& other)
{
	copyFrom(other);
}

template<typename T>
inline HeterogeneousStack<T>& HeterogeneousStack<T>::operator=(const HeterogeneousStack& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template<typename T>
inline HeterogeneousStack<T>::HeterogeneousStack(HeterogeneousStack&& other) noexcept
{
	moveFrom(std::move(other));
}

template<typename T>
inline HeterogeneousStack<T>& HeterogeneousStack<T>::operator=(HeterogeneousStack&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template<typename T>
inline size_t HeterogeneousStack<T>::getSize() const
{
	return this->size;
}

template<typename T>
inline size_t HeterogeneousStack<T>::getCapacity() const
{
	return this->capacity;
}

template<typename T>
inline HeterogeneousStack<T>& HeterogeneousStack<T>::push(const T& elem)
{
	if (getSize() >= getCapacity())
	{
		resize(getCapacity() * 2);
	}

	this->data[this->size++] = elem.clone();

	return *this;
}

template<typename T>
inline HeterogeneousStack<T>& HeterogeneousStack<T>::push(T&& elem)
{
	if (getSize() >= getCapacity())
	{
		resize(getCapacity() * 2);
	}

	this->data[this->size++] = std::move(new T(std::move(elem)));

	return *this;
}

template<typename T>
inline HeterogeneousStack<T>& HeterogeneousStack<T>::pop()
{
	if (getSize() == 0) 
	{
		return *this;
	}

	delete this->data[--this->size];
	this->data[this->size] = nullptr;

	if ((getSize() * 4) <= getCapacity() && getCapacity() > 1) 
	{
		resize(getCapacity() / 2);
	}

	return *this;
}

template<typename T>
inline const T& HeterogeneousStack<T>::top() const
{
	return *this->data[this->size - 1];
}

template<typename T>
inline HeterogeneousStack<T>::~HeterogeneousStack() noexcept
{
	free();
}

template<typename T>
inline void HeterogeneousStack<T>::resize(size_t newCapacity)
{
	T** newData = new T * [newCapacity];
	for (size_t i = 0; i < getSize(); i++)
	{
		newData[i] = this->data[i];
	}

	delete[] this->data;
	this->data = newData;
	this->capacity = newCapacity;
}

template<typename T>
inline unsigned int HeterogeneousStack<T>::getNextPowerOfTwo(unsigned int n) const
{
	if (n == 0) return 1;

	while (n & (n - 1))
	{
		n &= (n - 1);
	}

	return n << 1;
}

template<typename T>
inline unsigned int HeterogeneousStack<T>::allocateCapacity(unsigned int n) const
{
	return std::max(getNextPowerOfTwo(n + 1), 8u);
}

template<typename T>
inline void HeterogeneousStack<T>::copyFrom(const HeterogeneousStack& other)
{
	this->size = other.size;
	this->capacity = other.capacity;

	this->data = new T* [this->capacity];
	for (size_t i = 0; i < this->size; ++i)
	{
		this->data[i] = other.data[i]->clone();
	}
}

template<typename T>
inline void HeterogeneousStack<T>::moveFrom(HeterogeneousStack&& other) noexcept
{
	this->data = other.data;
	this->size = other.size;
	this->capacity = other.capacity;

	other.data = nullptr;
	other.size = other.capacity = 0;
}

template<typename T>
inline void HeterogeneousStack<T>::free()
{
	for (size_t i = 0; i < this->size; ++i) 
	{
		delete this->data[i];
	}

	delete[] this->data;
	this->data = nullptr;
	this->size = this->capacity = 0;
}