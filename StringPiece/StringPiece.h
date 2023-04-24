#include <iostream>

class StringPiece
{
    private:
        char* _string;
        size_t length;
    public:
        StringPiece();
        StringPiece(const char* string);
        ~StringPiece();
};
