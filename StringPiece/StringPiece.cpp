#include "StringPiece.h"

void StringPiece::CopyMemberData(const StringPiece& copy)
{
    stpcpy(dataBuffer, copy.dataBuffer);
    start = copy.start;
    end = copy.end;
}

void StringPiece::FreeMemberData()
{
    dataBuffer[0] = '\0';
    start = 0;
    end = 0;
}

unsigned StringPiece::GetBufferIndex(unsigned index) const
{
    return (start + index) % MAX_PIECE_LENGTH;
}

unsigned StringPiece::GetBufferIndexBack(unsigned index) const
{
    return (MAX_PIECE_LENGTH + end - index) % MAX_PIECE_LENGTH;
}

char* StringPiece::GetBufferAddress(int index) const
{
    return (char*)dataBuffer + index;
}

StringPiece::StringPiece(const char* string)
{
    size_t len = strlen(string) + 1;

    if(len <= MAX_PIECE_LENGTH)
    {
        start = 0;
        end = start + (len - 1);
        strcpy(dataBuffer, string);
    }
    else
        FreeMemberData();
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

}

const char* StringPiece::Value(char* buffer) const
{
    char current = dataBuffer[GetBufferIndex(0)];
    buffer[0] = current;
    size_t i = 1;
    for (;i < StringPiece::MAX_PIECE_LENGTH; i++)
    {
        current = dataBuffer[GetBufferIndex(i)];
        buffer[i] = current;
        if (current == '\0')
            break; 
    }
        
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
    char digits[10]; //ceil(log_10(unsigned max_value)) = 10;
    return operator<<(output, ToString(digits, piece));
}

StringPiece& operator<< (StringPiece& output, const char* piece)
{
    size_t outLen = output.Length(), pieceLen = strlen(piece);
    size_t capacity = outLen + pieceLen + 1;

    char* buffer = output.GetBufferAddress(output.end);
    for (size_t i = 0; i < pieceLen && output.Length() <= StringPiece::MAX_PIECE_LENGTH; i++)
        buffer[i] = piece[i];
        
    return output;
    
}

StringPiece& operator>> (unsigned piece, StringPiece& output)
{
    char digits[10]; //ceil(log_10(unsigned max_value)) = 10;
    return operator>>(ToString(digits, piece), output);
}

StringPiece& operator>> (const char* piece, StringPiece& output)
{
    size_t outLen = output.Length(), pieceLen = strlen(piece);
    size_t capacity = outLen + pieceLen + 1;
    
    if (capacity <=  StringPiece::MAX_PIECE_LENGTH)
    {
        char* address = output.GetBufferAddress(output.start - pieceLen);
        if (address < (char*)output.dataBuffer)
            address += StringPiece::MAX_PIECE_LENGTH;
            
        strcpy(address, piece);
        output.start = address - (char*)output.dataBuffer;
    }

    return output;
}

void StringPiece::Print(std::ostream& output) const
{
    size_t len = Length();
    for (size_t i = 0; i < len; i++)
        output << dataBuffer[GetBufferIndex(i)];
    
}

StringPiece::~StringPiece()
{
    FreeMemberData();
}