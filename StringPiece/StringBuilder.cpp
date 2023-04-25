#include "StringBuilder.h"

StringBuilder::StringBuilder(unsigned capacity): _capacity(capacity)
{
    _pieces = new StringPiece*[_capacity];
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

size_t StringBuilder::CurrentStringLength() const
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

U_String StringBuilder::CurrentString() const
{
    U_String result;
    for (size_t i = 0; i < _count; i++)
        if (_pieces[i] != nullptr)
        {
            char value[StringPiece::MAX_PIECE_LENGTH];
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
    for (size_t i = 0; i < _count; i++)
    {
        delete _pieces[i];
        _pieces[i] = nullptr;
    }
    delete[] _pieces;
    _pieces = nullptr;
    
}