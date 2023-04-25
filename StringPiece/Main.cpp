#include <iostream>
#include "StringBuilder.h"
#include "String.h"

int main()
{
    StringBuilder builder(4);
    builder.AddPiece("test");
    builder.AddPiece();
    builder.AddPiece("pepe");
    
    return 0;
}