// Clase derivada de Base
#ifndef DERIVED_H
#define DERIVED_H
#include "base.h"

class Derived : public Base
{
  public:
    Derived() {}
    ~Derived() {}

    virtual int foo() {return 10;}
};

#endif
