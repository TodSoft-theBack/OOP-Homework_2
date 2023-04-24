#include <iostream>
#include "StringPiece.h"

class StringBuilder
{
    private:
        StringPiece** _pieces = nullptr;
        size_t _count = 0;
        size_t _capacity = 0;
        
    public:
        void AddPiece(const StringPiece piece);
        StringBuilder(unsigned capacity);
        ~StringBuilder();
};