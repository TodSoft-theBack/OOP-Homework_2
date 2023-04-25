#include "StringSSO_Union.h"

StringSSOUnion operator+(const StringSSOUnion& lhs, const StringSSOUnion& rhs)
{
	char* result = new char[lhs.Length() + rhs.Length() + 1];
	result[0] = '\0';
	strcat(result, lhs.Data());
	strcat(result, rhs.Data());

	StringSSOUnion resultString(result);
	return resultString;
}

StringSSOUnion& StringSSOUnion::operator+=(const StringSSOUnion& other)
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

StringSSOUnion::StringSSOUnion()
{
	capacity = SMALL_STRING_MAX_SIZE;
	_data._static[0] = '\0';
}
StringSSOUnion::StringSSOUnion(const char* data)
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

StringSSOUnion::StringSSOUnion(const StringSSOUnion& StringSSOUnion)
{
	CopyMemberData(StringSSOUnion);
}

StringSSOUnion& StringSSOUnion::operator=(const StringSSOUnion& StringSSOUnion)
{
	if (this != &StringSSOUnion)
	{
		FreeMemberData();
        CopyMemberData(StringSSOUnion);
	}
	return *this;
}


void StringSSOUnion::FreeMemberData()
{
	if(!IsSmallString())
	{
		delete[] _data._dynamic._string;
		_data._dynamic._string = nullptr;
	}
}

StringSSOUnion::~StringSSOUnion()
{
	FreeMemberData();
}

size_t StringSSOUnion::Length() const
{
	if(IsSmallString())
		return strlen(_data._static);
	return _data._dynamic._length;
}
const char* StringSSOUnion::Data() const
{
	if (IsSmallString())
		return _data._static;
	return _data._dynamic._string;
}

bool StringSSOUnion::IsSmallString() const
{
	return capacity	== SMALL_STRING_MAX_SIZE;
}

void StringSSOUnion::CopyMemberData(const StringSSOUnion& copy)
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

char& StringSSOUnion::operator[](unsigned index)
{
	if(IsSmallString())
		return _data._static[index];
	else
		return _data._dynamic._string[index];
}

char StringSSOUnion::operator[](unsigned index) const 
{
	if(IsSmallString())
		return _data._static[index];
	else
		return _data._dynamic._string[index];
}

std::ostream& operator<<(std::ostream& output, const StringSSOUnion& string)
{
	if(string.IsSmallString())
		return output << string._data._static;
	else
		return output << string._data._dynamic._string;
   
}

