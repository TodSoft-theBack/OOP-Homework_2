#include "StringPiece.h"

void StringPiece::CopyMemberData(const StringPiece& copy)
{
    for (size_t i = 0; i < MAX_PIECE_LENGTH; i++)
        dataBuffer[i] = copy.dataBuffer[i];
    start = copy.start;
    end = copy.end;
}

void StringPiece::FreeMemberData()
{
    start = 0;
    end = 0;
}

unsigned StringPiece::GetBufferIndex(unsigned index) const
{
    return (start + index) % MAX_PIECE_LENGTH;
}

unsigned StringPiece::GetBufferIndexBack(unsigned index) const
{
    return (end + MAX_PIECE_LENGTH - index) % MAX_PIECE_LENGTH;
}

char* StringPiece::GetBufferAddress(int index) const
{
    return (char*)dataBuffer + index;
}

StringPiece::StringPiece(const char* string)
{
    SetValue(string);
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

char StringPiece::operator[](unsigned index) const
{
    return dataBuffer[GetBufferIndex(index)];
}

char& StringPiece::operator[](unsigned index)
{
    return dataBuffer[GetBufferIndex(index)];
}

void StringPiece::RemoveFront(unsigned count)
{
    unsigned newStart = GetBufferIndex(count);
    if (newStart != end)
        start = newStart;
    else
        FreeMemberData();
    
}

void StringPiece::RemoveBack(unsigned count)
{
    unsigned newEnd = GetBufferIndexBack(count);
    if (newEnd != start)
        end = newEnd;
    else
       FreeMemberData();
}

size_t StringPiece::Length() const
{
    return (MAX_PIECE_LENGTH + end - start) % MAX_PIECE_LENGTH;
}

void StringPiece::SetValue(const char* value)
{
    size_t capacity = strlen(value);
    start = 0;
    if (capacity > MAX_PIECE_LENGTH)
        end = MAX_PIECE_LENGTH - 1;
    else
        end = capacity - 1;
    for (size_t i = start; i <= end; i++)
        dataBuffer[i] = value[i];
    
}

const char* StringPiece::Value(char* buffer) const
{
    size_t index = 1;
    buffer[0] = dataBuffer[start];
    for (size_t i = (start + 1) % MAX_PIECE_LENGTH; i != end; ++i %= MAX_PIECE_LENGTH)
        buffer[index++] = dataBuffer[i];
    buffer[index++] = dataBuffer[end];
    buffer[index] = '\0';
    return buffer;
}

size_t CountDigits(unsigned integer)
{
    size_t count = 0;
    for (; integer != 0; integer /= 10)
        count++;
    return count;
}

char* ToString(char* buffer, unsigned integer)
{
    size_t count = CountDigits(integer);
    for (int i = count - 1; i >= 0; i--, integer /= 10)
        buffer[i] = '0' + integer % 10;   
    return buffer;
}

StringPiece& operator<< (StringPiece& output, unsigned piece)
{
    char digits[10];
    return operator<<(output, ToString(digits, piece));
}

StringPiece& operator<< (StringPiece& output, const char* piece)
{
    size_t outLen = output.Length(), pieceLen = strlen(piece);
    size_t newEnd = (output.end + pieceLen) % StringPiece::MAX_PIECE_LENGTH;

    size_t index = 0;
    for (size_t i = output.end; index < pieceLen ; ++i %= StringPiece::MAX_PIECE_LENGTH)
    {
        output.dataBuffer[i] = piece[index++];
    }
    
    output.end = newEnd;
    return output;
    
}

StringPiece& operator>> (unsigned piece, StringPiece& output)
{
    char digits[16];
    return operator>>(ToString(digits, piece), output);
}

StringPiece& operator>> (const char* piece, StringPiece& output)
{
    size_t outLen = output.Length(), pieceLen = strlen(piece);

    size_t newStart = (output.start + StringPiece::MAX_PIECE_LENGTH - pieceLen) % StringPiece::MAX_PIECE_LENGTH;

    size_t index = 0;
    for (size_t i = newStart; index < pieceLen ; ++i %= StringPiece::MAX_PIECE_LENGTH)
        output.dataBuffer[i] = piece[index++];
    output.start = newStart;

    return output;
}

StringPiece::~StringPiece()
{
    FreeMemberData();
}