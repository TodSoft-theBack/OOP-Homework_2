#pragma once
#include <iostream>
#include <cstring>

class U_String
{
    static const unsigned SMALL_STRING_MAX_SIZE = sizeof(size_t) + sizeof(char*);

    private:

		union 
		{
			char _static[SMALL_STRING_MAX_SIZE];
			struct
			{
				char* _string;
	    		size_t _length;
			} _dynamic;
		} _data;
		size_t capacity;
        
	    void CopyMemberData(const U_String& copy);
	    void FreeMemberData();
		bool IsSmallString() const;
		const char* Data() const;

    public:

	    U_String();
	    U_String(const char* string);
	    U_String(const U_String& copy);
	    U_String& operator=(const U_String& U_String);
	    size_t Length() const;
	    U_String& operator+=(const U_String& rhs);
	    char& operator[](unsigned index);
	    char operator[](unsigned index) const;

        friend std::ostream& operator<<(std::ostream& output, const U_String& string);
        friend std::istream& operator>>(std::istream& output, U_String& string);
		friend U_String operator+(const U_String& lhs, const U_String& rhs);
	    ~U_String();
};