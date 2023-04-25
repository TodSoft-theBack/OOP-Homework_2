#include <iostream>
#include <cstring>

class StringSSOUnion
{
    static const unsigned SMALL_STRING_MAX_SIZE = sizeof(size_t) + sizeof(char*);

    private:

		union 
		{
			char _static[SMALL_STRING_MAX_SIZE];
			struct DynamicData
			{
				char* _string;
	    		size_t _length;
			} _dynamic;
		} _data;
		size_t capacity;
        
	    void CopyMemberData(const StringSSOUnion& copy);
	    void FreeMemberData();
		bool IsSmallString() const;
		const char* Data() const;

    public:

	    StringSSOUnion();
	    StringSSOUnion(const char* string);
	    StringSSOUnion(const StringSSOUnion& copy);
	    StringSSOUnion& operator=(const StringSSOUnion& StringSSOUnion);
	    size_t Length() const;
	    StringSSOUnion& operator+=(const StringSSOUnion& rhs);
	    char& operator[](unsigned index);
	    char operator[](unsigned index) const;

        friend std::ostream& operator<<(std::ostream& output, const StringSSOUnion& string);
		friend StringSSOUnion operator+(const StringSSOUnion& lhs, const StringSSOUnion& rhs);
	    ~StringSSOUnion();
};