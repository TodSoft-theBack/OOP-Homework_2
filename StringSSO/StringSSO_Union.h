#include <iostream>
#include <cstring>

class StringSSOUnion
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
	    void CopyMemberData(const StringSSOUnion& copy);
	    void FreeMemberData();
		void MoveMemberData(StringSSOUnion&& temporary);
		bool IsSmallString() const;

    public:

		//Constructors
	    StringSSOUnion();
		StringSSOUnion(size_t capacity);
	    StringSSOUnion(const char* string);
	    StringSSOUnion(const StringSSOUnion& copy);
		StringSSOUnion(StringSSOUnion&& temporary);

		//Public interface
		size_t Length() const;
		const char* Data() const;

		//Operators
	    StringSSOUnion& operator=(const StringSSOUnion& string);
		StringSSOUnion& operator=(StringSSOUnion&& temporary);       
	    StringSSOUnion& operator+=(const StringSSOUnion& rhs);
	    char& operator[](unsigned index);
	    char operator[](unsigned index) const;

		friend StringSSOUnion operator+(const StringSSOUnion& lhs, const StringSSOUnion& rhs);
        friend std::ostream& operator<<(std::ostream& output, const StringSSOUnion& string);
		friend std::istream& operator>>(std::istream& output, StringSSOUnion& string);

		//Destructor
	    ~StringSSOUnion();
};