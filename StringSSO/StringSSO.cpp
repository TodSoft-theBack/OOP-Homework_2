#include "StringSSO.h"

StringSSO operator+(const StringSSO& lhs, const StringSSO& rhs)
{
	size_t thisLen = lhs.Length(), thatLen = rhs.Length();
	char* result = new char[lhs.Length() + rhs.Length() + 1];
	
	for (size_t i = 0; i < thisLen; i++)
		result[i] = lhs[i];

	for (size_t i = thisLen; i <= thisLen + thatLen + 1; i++)
		result[i] = rhs[i - thisLen];
	

	StringSSO resultString(result);

	return resultString;
}

StringSSO& StringSSO::operator+=(const StringSSO& rhs)
{
	size_t thisLen = Length(), thatLen = rhs.Length();
	size_t resultCapacity = thisLen + thatLen + 1;

	if(resultCapacity <= SMALL_STRING_MAX_SIZE)
	{
		for (size_t i = 0; i <= thatLen; i++)
			SetAt(thisLen + i, rhs[i]);
		return *this;
	}

	capacity = resultCapacity;
	char* result = new char[capacity];

	for (size_t i = 0; i < thisLen; i++)
		result[i] = (*this)[i];

	for (size_t i = thisLen; i <= thisLen + thatLen + 1; i++)
		result[i] = rhs[i - thisLen];
	

	if (!IsSmallString())	
		delete[] _data;

	_data = result;
	_length = capacity - 1;

	return *this;
}

StringSSO::StringSSO()
{
	_data = nullptr;
	SetAt(0, '\0');
	capacity = SMALL_STRING_MAX_SIZE;
}

StringSSO::StringSSO(const char* data)
{
	size_t len = strlen(data) + 1;
	if(len <= SMALL_STRING_MAX_SIZE)
	{
		for (size_t i = 0; i < len; i++)
			this->SetAt(i, data[i]);
		capacity = SMALL_STRING_MAX_SIZE;
		return;
	}

	_data = new char[len];
	strcpy(_data, data);
	_length = len - 1;
	capacity = len;
}

StringSSO::StringSSO(const StringSSO& stringSSO)
{
	CopyMemberData(stringSSO);
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


void StringSSO::FreeMemberData()
{
	if(!IsSmallString())
		delete[] _data;
	_data = nullptr;
}

StringSSO::~StringSSO()
{
	FreeMemberData();
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

bool StringSSO::IsSmallString() const
{
	return capacity == SMALL_STRING_MAX_SIZE;
}

void StringSSO::CopyMemberData(const StringSSO& copy)
{
	if(copy.IsSmallString())
	{
		_length = copy._length;
		_data = copy._data;
		capacity = copy.capacity;
		return;
	}

	_length = copy._length;
	_data = new char[_length + 1];
	strcpy(_data, copy._data);
}

void StringSSO::SetAt(unsigned index, char value)
{
	size_t mask = 255;
	size_t bitshiftCount = 0;
	size_t byte = ~(unsigned char)value;
	if(index < sizeof(_data))
	{
		bitshiftCount = sizeof(_data) * index;
		mask <<= bitshiftCount;
		size_t data_memory = (size_t)_data;
		data_memory |= mask;
		byte <<= bitshiftCount;
		data_memory ^=  byte;
		_data = (char*)nullptr + data_memory;
	}
	else
	{
		bitshiftCount = sizeof(_length) * (index - sizeof(_data));
		mask <<= bitshiftCount;
		_length |= mask;
		byte <<= bitshiftCount;
		_length ^= byte;
	}	
}

char StringSSO::operator[](unsigned index) const 
{
	if(IsSmallString())
	{
		size_t mask = 255;

		size_t nthByte = 0;
		size_t bitshiftCount = 0;
		if(index < sizeof(_data))
		{
			bitshiftCount = sizeof(_data) * index;
			mask <<= bitshiftCount;
			nthByte = (size_t)_data & mask;
		}
		else
		{
			bitshiftCount = sizeof(_length) * (index - sizeof(_data));
			mask <<= bitshiftCount;
			nthByte = _length & mask;
		}	
		size_t res;
		res = nthByte >> bitshiftCount;
		return res == 0 ? '\0' : res;

	}
	return _data[index];
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