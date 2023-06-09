#include "StringBuilder.h"

void StringBuilder::CopyMemberData(const StringBuilder& copy)
{
    _pieces = new StringPiece*[copy._capacity];
    for (size_t i = 0; i < copy._count; i++)
        _pieces[i] = copy._pieces[i];
    _capacity = copy._capacity;
    _count = copy._count;
}

void StringBuilder::MoveMemberData(StringBuilder&& temporary)
{
    _pieces = temporary._pieces;
    temporary._pieces = nullptr;
    _capacity = temporary._capacity;
    _count = temporary._count;
}

void StringBuilder::FreeMemberData()
{
    for (size_t i = 0; i < _count; i++)
    {
        delete _pieces[i];
        _pieces[i] = nullptr;
    }
    delete[] _pieces;
    _pieces = nullptr;
}

StringBuilder::StringBuilder(unsigned capacity): _capacity(capacity)
{
    _pieces = new StringPiece*[_capacity];
    for (size_t i = 0; i < _capacity; i++)
        _pieces[i] = nullptr;
    
}

StringBuilder::StringBuilder(const StringBuilder& copy)
{
    CopyMemberData(copy);
}

StringBuilder::StringBuilder(StringBuilder&& temporary)
{
    MoveMemberData(std::move(temporary));
}

void StringBuilder::AddPiece(const char* piece)
{
    _pieces[_count++] = new StringPiece(piece);
}

void StringBuilder::AddPiece()
{
    _pieces[_count++] = new StringPiece();
}

void StringBuilder::InsertAt(unsigned index, StringPiece* element)
{
    if (_pieces[index] != nullptr)
        delete _pieces[index];
    _pieces[index] = element;    
}

void StringBuilder::RemoveAt(unsigned index)
{
    if (index >= _count)
        return;

    delete _pieces[index];
    _pieces[index] = nullptr;
}

void StringBuilder::Swap(unsigned first, unsigned second)
{
    if (first >= _count || second >= _count)
        return;
    StringPiece* temp = _pieces[first];
    _pieces[first] = _pieces[second];
    _pieces[second] = temp;
}

size_t StringBuilder::StringLength() const
{
    size_t aggregateLength = 0;

    for (size_t i = 0; i < _count; i++)
        if (_pieces[i] != nullptr)
            aggregateLength += _pieces[i]->Length();
        else
            if (i == _count - 2)
                aggregateLength += EMPTY_PIECE_SIZE;

    return aggregateLength;
}

U_String StringBuilder::String() const
{
    U_String result(StringLength() + 1);
    for (size_t i = 0; i < _count; i++)
        if (_pieces[i] != nullptr)
        {
            char value[StringPiece::MAX_PIECE_LENGTH + 1];
            result += _pieces[i]->Value(value);
        }
        else
            if (i == _count - 2)
            {
                char empty_piece[EMPTY_PIECE_SIZE];
                for (size_t i = 0; i < EMPTY_PIECE_SIZE; i++)
                    empty_piece[i] = ' ';
                result += empty_piece; 
            }
                
    return result;
}

StringBuilder& StringBuilder::operator=(const StringBuilder& stringBuilder)
{
    if (this != &stringBuilder)
    {
        FreeMemberData();
        CopyMemberData(stringBuilder);
    }
    return *this;
}
StringBuilder& StringBuilder::operator=(StringBuilder&& temporary)
{
    if (this != &temporary)
    {
        FreeMemberData();
        MoveMemberData(std::move(temporary));
    }
    return *this;
}

StringPiece StringBuilder::operator[](unsigned index) const
{
    return *_pieces[index];
}

StringPiece& StringBuilder::operator[](unsigned index)
{
    return *_pieces[index];
}

StringBuilder::~StringBuilder()
{
    FreeMemberData();
}