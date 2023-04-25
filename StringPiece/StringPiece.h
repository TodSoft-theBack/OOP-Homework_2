#include <iostream>
#include <cstring> /* Added because of strlen() because it says its undefined*/

class StringPiece
{
    public:
        static const size_t MAX_PIECE_LENGTH = 16;

    private:
        char* start = nullptr;
        char* end = nullptr;
        void CopyMemberData(const StringPiece& copy);
        void FreeMemberData();

    public:
        StringPiece() = default;
        StringPiece(const char* string);
        StringPiece(const StringPiece& copy);
        StringPiece& operator=(const StringPiece& piece);
        size_t Length() const;

        friend StringPiece operator<< (const StringPiece& output, const StringPiece& piece);
        friend StringPiece operator>> (const StringPiece& output, const StringPiece& piece);

    ~StringPiece();
};
