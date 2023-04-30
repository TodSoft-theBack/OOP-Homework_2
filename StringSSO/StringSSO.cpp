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

void StringSSO::MoveMemberData(StringSSO&& copy)
{
	if(!copy.IsSmallString())
	{
		_length = copy._length;
		_data = copy._data;
		copy._data = nullptr;
		_capacity = copy._capacity;
		return;
	}

	//copy static data here
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
	
}

StringSSO::StringSSO(const char* data)
{
	size_t capacity = strlen(data) + 1;
	if(capacity <= SMALL_STRING_MAX_SIZE)
	{
		for (size_t i = 0; i < capacity; i++)
			SetAt(i, data[i]);
		_capacity = SMALL_STRING_MAX_SIZE;
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

	if(resultCapacity <= SMALL_STRING_MAX_SIZE)
	{
		for (size_t i = 0; i <= thatLen; i++)
			(*this)[thisLen + i] =  rhs[i];
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
		bitshiftCount = sizeof(8) * index;
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

char& StringSSO::operator[](unsigned index)
{
	if (!IsSmallString())
		return _data[index];

	if(index < sizeof(_data))
		return ((char*)(&_data))[index];
	else
		return ((char*)(&_length))[index - sizeof(_data)];
}

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