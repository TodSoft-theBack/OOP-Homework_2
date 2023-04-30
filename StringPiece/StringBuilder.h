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

        void CopyMemberData(const StringBuilder& copy);
        void MoveMemberData(StringBuilder&& temporary);
        void FreeMemberData();

    public:
        StringBuilder(unsigned capacity);
        StringBuilder(const StringBuilder& copy);
        StringBuilder(StringBuilder&& temporary);
        void AddPiece(const char* piece);
        void AddPiece();
        void InsertAt(unsigned index, StringPiece* element);
        void RemoveAt(unsigned index);
        void Swap(unsigned first, unsigned second);
        size_t StringLength() const;
        U_String String() const;
        
        StringBuilder& operator=(const StringBuilder& stringBuilder);
        StringBuilder& operator=(StringBuilder&& temporary);
        StringPiece operator[](unsigned index) const;
        StringPiece& operator[](unsigned index);
    ~StringBuilder();
};