#include <iostream>
#include <cstring>

class StringSSO
{
    static const unsigned SMALL_STRING_MAX_SIZE = sizeof(size_t) + sizeof(char*);

    private:

        char* _data = nullptr;
	    size_t _length = 0;
		size_t capacity;
	    void CopyMemberData(const StringSSO& copy);
	    void FreeMemberData();
		bool IsSmallString() const;
    public:

	    StringSSO();
	    StringSSO(const char* string);
	    StringSSO(const StringSSO& copy);
	    StringSSO& operator=(const StringSSO& rhs);
	    size_t Length() const;
	    void SetAt(unsigned undex, char value);
	    char operator[](unsigned index) const;

        friend std::ostream& operator<<(std::ostream& output, const StringSSO& string);
		friend StringSSO operator+(const StringSSO& lhs, const StringSSO& rhs);
	    ~StringSSO();
};