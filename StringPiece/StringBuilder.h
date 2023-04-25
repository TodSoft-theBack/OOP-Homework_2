#include <iostream>
#include "StringPiece.h"
#include "U_String.h"

class StringBuilder
{
    static const size_t EMPTY_PIECE_SIZE = 20;

    private:
        StringPiece** _pieces = nullptr;
        size_t _count = 0;
        size_t _capacity = 0;

    public:
        StringBuilder(unsigned capacity);
        void AddPiece(const char* piece);
        void AddPiece();
        void InsertAt(unsigned index, StringPiece* element);
        void RemoveAt(unsigned index);
        void Swap(unsigned first, unsigned second);
        size_t CurrentStringLength() const;
        U_String CurrentString() const;
        
        StringPiece operator[](unsigned index) const;
        StringPiece& operator[](unsigned index);
    ~StringBuilder();
};