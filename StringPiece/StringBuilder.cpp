#include "StringBuilder.h"

StringBuilder::StringBuilder(unsigned capacity): _capacity(capacity)
{
    _pieces = new StringPiece*[_capacity];
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