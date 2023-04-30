#include "StringSSO.h"

void StringSSO::CopyMemberData(const StringSSO& copy)
{
	if(copy.IsSmallString())
	{
		_length = copy._length;
		_data = copy._data;
		_capacity = copy._capacity;
		return;
	}

	_length = copy._length;
	_data = new char[_length + 1];
	strcpy(_data, copy._data);
}

void StringSSO::MoveMemberData(StringSSO&& temporary)
{
	if(!temporary.IsSmallString())
	{
		_length = temporary._length;
		_data = temporary._data;
		temporary._data = nullptr;
		_capacity = temporary._capacity;
		return;
	}

	CopyMemberData(temporary);
}

void StringSSO::FreeMemberData()
{
	if(!IsSmallString())
		delete[] _data;
	_data = nullptr;
}

bool StringSSO::IsSmallString() const
{
	return _capacity == SMALL_STRING_MAX_SIZE;
}

StringSSO::StringSSO()
{
	_data = nullptr;
	_length = 0;
	_capacity = SMALL_STRING_MAX_SIZE;
}

StringSSO::StringSSO(size_t capacity) : StringSSO()
{
	if (capacity > SMALL_STRING_MAX_SIZE)
	{
		_data = new char[capacity];
		_data[0] = '\0';
		_length = 0;
		_capacity = capacity;
	}
	else
		_capacity = SMALL_STRING_MAX_SIZE;

}

StringSSO::StringSSO(const char* data)
{
	size_t capacity = strlen(data) + 1;
	if(capacity <= SMALL_STRING_MAX_SIZE)
	{
		_capacity = SMALL_STRING_MAX_SIZE;
		for (size_t i = 0; i < capacity; i++)
			(*this)[i] = data[i];
		return;
	}
	
	_data = new char[capacity];
	strcpy(_data, data);
	_length = capacity - 1;
	_capacity = capacity;
}

StringSSO::StringSSO(const StringSSO& string)
{
	CopyMemberData(string);
}

StringSSO::StringSSO(StringSSO&& temptorary)
{
	MoveMemberData(std::move(temptorary));
}


size_t StringSSO::Length() const
{
	if(IsSmallString())
	{
		size_t len = 0;
		for (size_t i = 0; (*this)[i] != '\0'; i++, len++);
			return len;
	}
	return _length;
}

StringSSO& StringSSO::operator=(const StringSSO& rhs)
{
	if (this != &rhs)
	{
		FreeMemberData();
        CopyMemberData(rhs);
	}
	return *this;
}

StringSSO& StringSSO::operator=(StringSSO&& temporary)
{
	if (this != &temporary)
	{
		FreeMemberData();
        MoveMemberData(std::move(temporary));
	}
	return *this;
}

StringSSO& StringSSO::operator+=(const StringSSO& rhs)
{
	size_t thisLen = Length(), thatLen = rhs.Length();
	size_t resultCapacity = thisLen + thatLen + 1;

	if(IsSmallString() && resultCapacity <= SMALL_STRING_MAX_SIZE)
	{
		for (size_t i = 0; i <= thatLen; i++)
			(*this)[thisLen + i] =  rhs[i];
		return *this;
	}

	if (!IsSmallString() && resultCapacity <= _capacity)
	{
		for (size_t i = 0; i <= thatLen; i++)
			_data[thisLen + i] = rhs[i];
		_length = resultCapacity - 1;
		return *this;
	}

	_capacity = resultCapacity;
	char* result = new char[_capacity];

	for (size_t i = 0; i < thisLen; i++)
		result[i] = (*this)[i];

	for (size_t i = thisLen; i <= thisLen + thatLen + 1; i++)
		result[i] = rhs[i - thisLen];
	

	if (!IsSmallString())	
		delete[] _data;

	_data = result;
	_length = _capacity - 1;

	return *this;
}

char StringSSO::operator[](unsigned index) const 
{
	if(!IsSmallString())
		return _data[index];

	size_t mask = 255;
	size_t nthByte = 0;
	size_t bitshiftCount = 0;

	if(index < sizeof(_data))
	{
		bitshiftCount = sizeof(_data) * index; //the amount of shifts we need to get the nth byte
		mask <<= bitshiftCount; //we shift the mask to the index of the byte we want
		nthByte = (size_t)_data & mask; //We extract the info by using bitwise "AND"
	}
	else
	{
		bitshiftCount = sizeof(_length) * (index - sizeof(_data)); //the amount of shifts we need to get the nth byte
		mask <<= bitshiftCount; //we shift the mask to the index of the byte we want
		nthByte = _length & mask; //We extract the info by using bitwise "AND"
	}	
	size_t res;
	res = nthByte >> bitshiftCount; //revert the bitshift to retrieve the value of the char at the desired index
	return res == 0 ? '\0' : res;	
}

char& StringSSO::operator[](unsigned index)
{
	if (!IsSmallString())
		return _data[index];

	//this converts the pointer itselt into an array of bytes(chars) which I can index and return
	if(index < sizeof(_data))
		return ((char*)(&_data))[index]; 
	else
		return ((char*)(&_length))[index - sizeof(_data)];
}

StringSSO operator+(const StringSSO& lhs, const StringSSO& rhs)
{
	size_t thisLen = lhs.Length(), thatLen = rhs.Length();
	StringSSO result(thisLen + thatLen + 1);
	result += lhs;
	result += rhs;
	return result;
}

std::ostream& operator<<(std::ostream& output, const StringSSO& string)
{
	if(string.IsSmallString())
	{
		for (size_t i = 0; i < StringSSO::SMALL_STRING_MAX_SIZE; i++)
		{
			char current = string[i];
			if(current == '\0')
				return output;
			output << current;
		}
		return output;
	}
    return output << string._data;
}

StringSSO::~StringSSO()
{
	FreeMemberData();
}