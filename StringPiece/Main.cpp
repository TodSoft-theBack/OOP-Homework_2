#include <iostream>
#include "StringBuilder.h"
#include "U_String.h"

int main()
{
    StringBuilder builder(4);
    
    builder.AddPiece("test");
    builder.AddPiece();
    builder.AddPiece("football");

    builder[1] << " friends ";
    " Hello " >> builder[1];
    10 >> builder[2];

    U_String result1 = builder.CurrentString();
    std::cout << result1 << std::endl;

    builder.Swap(1,2);
    U_String result2 = builder.CurrentString();
    std::cout << result2 << std::endl;

    builder.RemoveAt(1);
    U_String result3 = builder.CurrentString();
    std::cout << result3 << std::endl;

    return 0;
}