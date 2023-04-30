#include <iostream>
#include "StringSSO_Union.h"
#include "StringSSO.h"
#define console std::cout
#define nl std::endl

int main()
{

  console << sizeof(StringSSO) << nl;
  console << sizeof(StringSSOUnion) << nl;
  //In my opinion this approach is more ellegant to the bitwise one
  //However, the second approach keeps the simplisity of storing the data

  //String class using union to store the data 
  StringSSOUnion emptyUnion;
  StringSSOUnion smallUnion("small");
  StringSSOUnion bigUnion("Muda muda muda muda muda muda muda muda ");
  smallUnion += " Pepe";
  StringSSOUnion testUnion = "\n" + bigUnion ;
  testUnion += bigUnion;
  console << "First: " << emptyUnion + smallUnion << "\nSecond: " << smallUnion << testUnion << std::endl;

  //String class using bitwise operations to store the data
  StringSSO empty;
  StringSSO small("small");
  StringSSO big("Ho! Are you approaching me? *jojo pose battle*");
  small += " pp";
  small[5] = '_';
  StringSSO test = "\n" + big ;
  test += "\n" + big;
  console << "First: " << empty + small << "\nSecond: " << small << test << std::endl;
  return 0;
}
