#include "StringPiece.h"

void StringPiece::CopyMemberData(const StringPiece& copy)
{
    size_t len = copy.Length();
}

void StringPiece::FreeMemberData()
{
    delete[] start;
    start = nullptr;
    end = nullptr;
}

StringPiece::StringPiece(const char* string)
{
    size_t len = strlen(string) + 1;

    if(len < MAX_PIECE_LENGTH)
    {
        start = new char[len];
        end = start + len;
        strcpy(start, string);
    }
    else
    {
        start = nullptr;
        end = nullptr;
    }
}

StringPiece::StringPiece(const StringPiece& copy)
{
    CopyMemberData(copy);
}

StringPiece& StringPiece::operator=(const StringPiece& piece)
{
    if(this != &piece)
    {
        FreeMemberData();
        CopyMemberData(piece);
    }
    return *this;
}

size_t StringPiece::Length() const
{
    int length = end - start;
    return length < 0 ? length + MAX_PIECE_LENGTH : length;
}

StringPiece operator<< (StringPiece& output, const StringPiece& piece)
{
    size_t outLen = output.Length(), pieceLen = piece.Length();
    size_t capacity = outLen + pieceLen + 1;
    if (capacity <  StringPiece::MAX_PIECE_LENGTH)
    {
        
    }
    
}

StringPiece operator>> (StringPiece& output, const StringPiece& piece)
{

}

StringPiece::~StringPiece()
{
    delete[] start;
    start = nullptr;
    end = nullptr;
}