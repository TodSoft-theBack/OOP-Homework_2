#pragma once
#include <iostream>
#include <cstring>

class U_String
{
    static const unsigned SMALL_STRING_MAX_SIZE = sizeof(size_t) + sizeof(char*);

    private:

		//Data
		union 
		{
			char _static[SMALL_STRING_MAX_SIZE];
			struct
			{
				char* _string;
	    		size_t _length;
			} _dynamic;
		} _data;
		size_t _capacity;
        
		//Private fucntions
	    void CopyMemberData(const U_String& copy);
	    void FreeMemberData();
		void MoveMemberData(U_String&& temporary);
		bool IsSmallString() const;

    public:

		//Constructors
	    U_String();
		U_String(size_t capacity);
	    U_String(const char* string);
	    U_String(const U_String& copy);
		U_String(U_String&& temporary);

		//Public interface
		size_t Length() const;
		const char* Data() const;

		//Operators
	    U_String& operator=(const U_String& string);
		U_String& operator=(U_String&& temporary);       
	    U_String& operator+=(const U_String& rhs);
	    char& operator[](unsigned index);
	    char operator[](unsigned index) const;

		friend U_String operator+(const U_String& lhs, const U_String& rhs);
        friend std::ostream& operator<<(std::ostream& output, const U_String& string);
		friend std::istream& operator>>(std::istream& output, U_String& string);

		//Destructor
	    ~U_String();
};