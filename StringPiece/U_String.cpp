#include "U_String.h"


U_String operator+(const U_String& lhs, const U_String& rhs)
{
	char* result = new char[lhs.Length() + rhs.Length() + 1];
	result[0] = '\0';
	strcat(result, lhs.Data());
	strcat(result, rhs.Data());

	U_String resultString(result);
	return resultString;
}

U_String& U_String::operator+=(const U_String& other)
{
	size_t thisLen = Length(), thatLen = other.Length();
	size_t resultCapacity = thisLen + thatLen + 1;

	if (resultCapacity <= SMALL_STRING_MAX_SIZE)
	{
		strcat(_data._static, other.Data());
		return *this;
	}
	
	char* result = new char[resultCapacity];
	result[0] = '\0';
	strcat(result, Data());
	strcat(result, other.Data());

	if (!IsSmallString())
		delete[] _data._dynamic._string;
	
	_data._dynamic._string = result;
	_data._dynamic._length = resultCapacity - 1;
	capacity = resultCapacity;

	return *this;
}

U_String::U_String()
{
	capacity = SMALL_STRING_MAX_SIZE;
	_data._static[0] = '\0';
}
U_String::U_String(const char* data)
{
	size_t len = strlen(data) + 1;
	capacity = SMALL_STRING_MAX_SIZE;
	if(len <= SMALL_STRING_MAX_SIZE)
		strcpy(_data._static, data);
	else
	{
		_data._dynamic._string = new char[len];
		_data._dynamic._length = len - 1;
		strcpy(_data._dynamic._string, data);
		capacity = len;
	}
	
}

U_String::U_String(const U_String& U_String)
{
	CopyMemberData(U_String);
}

U_String& U_String::operator=(const U_String& U_String)
{
	if (this != &U_String)
	{
		FreeMemberData();
        CopyMemberData(U_String);
	}
	return *this;
}


void U_String::FreeMemberData()
{
	if(!IsSmallString())
	{
		delete[] _data._dynamic._string;
		_data._dynamic._string = nullptr;
	}
}

U_String::~U_String()
{
	FreeMemberData();
}

size_t U_String::Length() const
{
	if(IsSmallString())
		return strlen(_data._static);
	return _data._dynamic._length;
}
const char* U_String::Data() const
{
	if (IsSmallString())
		return _data._static;
	return _data._dynamic._string;
}

bool U_String::IsSmallString() const
{
	return capacity	== SMALL_STRING_MAX_SIZE;
}

void U_String::CopyMemberData(const U_String& copy)
{
	if(copy.IsSmallString())
	{
		strcpy(_data._static, copy._data._static);
		capacity = SMALL_STRING_MAX_SIZE;
	}
	else
	{
		capacity = copy.capacity;
		_data._dynamic._string = new char[capacity];
	}
}

char& U_String::operator[](unsigned index)
{
	if(IsSmallString())
		return _data._static[index];
	else
		return _data._dynamic._string[index];
}

char U_String::operator[](unsigned index) const 
{
	if(IsSmallString())
		return _data._static[index];
	else
		return _data._dynamic._string[index];
}

std::ostream& operator<<(std::ostream& output, const U_String& string)
{
	if(string.IsSmallString())
		return output << string._data._static;
	else
		return output << string._data._dynamic._string;
   
}

std::istream& operator>>(std::istream& input, U_String& string)
{
    if(string.IsSmallString())
		return input >> string._data._static;
	else
	{
        char buffer[256];
        input >> buffer;
        string = buffer;
        return input;
    }
   
}