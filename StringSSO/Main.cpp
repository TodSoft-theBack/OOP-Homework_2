#include <iostream>
#include "StringSSO_Union.h"
#include "StringSSO.h"
#define console std::cout

int main()
{

  console << sizeof(StringSSO) << std::endl;
  console << sizeof(StringSSOUnion) << std::endl;
  //In my opinion this approach is more ellegant to the bitwise one
  //However, the second approach keeps the simplisity of storing the data

  //String class using union to store the data 
  StringSSOUnion emptyUnion;
  StringSSOUnion smallUnion("small");
  StringSSOUnion bigUnion("Muda muda muda muda muda muda muda muda ");
  smallUnion += " Pepe";
  StringSSOUnion testUnion = "\n" + bigUnion ;
  testUnion += testUnion;
  console << "First: " << emptyUnion + smallUnion << "\nSecond: " << smallUnion << testUnion << std::endl;

  //String class using bitwise operations to store the data into the pointer and its corresponding length
  StringSSO empty;
  StringSSO small("small");
  StringSSO big("Ho! Are you approaching me? *jojo pose battle*");
  console << small << std::endl;
  small += " pp";
  console << small << std::endl;
  small[5] = '_';
  console << small << std::endl;
  StringSSO test = "\n" + big ;
  test += "\n" + big;
  console << "First: " << empty + small << "\nSecond: " << small << test << std::endl;
  return 0;
}
