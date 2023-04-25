#include <iostream>
#include "StringSSO_Union.h"
#include "StringSSO.h"

int main()
{
  
  //In my opinion this approach is more ellegant to the bitwise one
  //However, the second approach keeps the simplisity of storing the data

  //String class using union to store the data 
  StringSSOUnion emptyUnion;
  StringSSOUnion smallUnion("small");
  StringSSOUnion bigUnion("Muda muda muda muda muda muda muda muda ");
  smallUnion += " Pepe";
  StringSSOUnion testUnion = "\n" + bigUnion ;
  testUnion += bigUnion;
  std::cout << "First: " << emptyUnion + smallUnion << "\nSecond: " << smallUnion << testUnion << std::endl;

  //String class using bitwise operations to store the data
  StringSSO empty;
  StringSSO small("small");
  StringSSO big("Ho! Are you approaching me? *jojo pose battle*");
  small += " Pepe";
  StringSSO test = "\n" + big ;
  test += "\n" + big;
  std::cout << "First: " << empty + small << "\nSecond: " << small << test << std::endl;
  return 0;
}
