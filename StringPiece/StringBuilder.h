#include <iostream>
#include "StringPiece.h"
#include "String.h"

class StringBuilder
{
    private:
        StringPiece** _pieces = nullptr;
        size_t _count = 0;
        size_t _capacity = 0;

    public:
        void AddPiece(const StringPiece piece);
        void AddPiece();
        StringBuilder(unsigned capacity);
        StringPiece operator[](unsigned index) const;
        StringPiece& operator[](unsigned index);
        String C_String() const;
    ~StringBuilder();
};