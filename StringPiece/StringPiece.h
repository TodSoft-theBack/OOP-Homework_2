#include <iostream>
#include <cstring> /* Added because of strlen(), stcpy() and strcat() because it says its undefined*/

class StringPiece
{
    public:
        static const size_t MAX_PIECE_LENGTH = 16;

    private:
        char dataBuffer[MAX_PIECE_LENGTH];
        unsigned start = 0;
        unsigned end = 0;
        void CopyMemberData(const StringPiece& copy);
        void FreeMemberData();
        unsigned GetBufferIndex(unsigned index) const;
        unsigned GetBufferIndexBack(unsigned index) const;
        char* GetBufferAddress(int index) const;

    public:
        StringPiece() = default;
        StringPiece(const char* string);
        StringPiece(const StringPiece& copy);
        StringPiece& operator=(const StringPiece& piece);
        char operator[](unsigned index) const;
        char& operator[](unsigned index);
        void RemoveFront(unsigned count);
        void RemoveBack(unsigned count);
        size_t Length() const;

        void SetValue(const char* value);
        const char* Value(char* buffer) const;

        void Print(std::ostream& output) const;

        friend StringPiece& operator<< (StringPiece& output, const char* piece);
        friend StringPiece& operator>> (const char* piece, StringPiece& output);

        friend StringPiece& operator<< (StringPiece& output, unsigned piece);
        friend StringPiece& operator>> (unsigned piece, StringPiece& output);

    ~StringPiece();
};
