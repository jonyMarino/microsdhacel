#ifndef _MATH_HPP
#define _MATH_HPP

#include "./PE/include/PE_Types.h"

class Math{
  public:
    static unsigned int pow10(byte exponente); /*exponente esta entre 0 y 4*/
  private:
    static const unsigned int div_dec[5];
};


#endif