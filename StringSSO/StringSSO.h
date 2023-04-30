#include <iostream>
#include <cstring> //the code is compiled in g++ which requires this for strlen() strcat() and strcmp()

class StringSSO
{
    static const unsigned SMALL_STRING_MAX_SIZE = sizeof(size_t) + sizeof(char*);

    private:
		//data
        char* _data = nullptr;
	    size_t _length = 0;
		size_t _capacity;

		//Private functions
	    void CopyMemberData(const StringSSO& copy);
	    void FreeMemberData();
		void MoveMemberData(StringSSO&& temporary);
		bool IsSmallString() const;

    public:

		//Constructors
	    StringSSO();
		StringSSO(size_t capacity);
	    StringSSO(const char* string);
	    StringSSO(const StringSSO& string);
		StringSSO(StringSSO&& temporary);

		//Public interface
	    size_t Length() const;
		
		//Operators
		StringSSO& operator=(const StringSSO& rhs);
		StringSSO& operator=(StringSSO&& rhs);
		StringSSO& operator+=(const StringSSO& rhs);
	    char operator[](unsigned index) const;
		char& operator[](unsigned index);
		
		friend StringSSO operator+(const StringSSO& lhs, const StringSSO& rhs);
        friend std::ostream& operator<<(std::ostream& output, const StringSSO& string);
		friend std::istream& operator>>(std::istream& output, StringSSO& string);
		
		//Destructor
	    ~StringSSO();
};