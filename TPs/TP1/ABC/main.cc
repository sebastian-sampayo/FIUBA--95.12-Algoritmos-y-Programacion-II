#include <iostream>
#include "base.h"
#include "derived.h"
using namespace std;

int
main ()
{
  Base *b;
  Derived d;
  
  //b = &d;
  cout << d.foo() << endl;
  cout << b->foo() << endl;
  return 0;
}
