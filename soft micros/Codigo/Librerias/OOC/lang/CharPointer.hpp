#ifndef _CHAR_POINTER_HPP
#define _CHAR_POINTER_HPP

#include "./PE/include/PE_Types.h"

class CharPointer{
  public:
    static void printFloat(char * str,int integer,byte decimalPosition);
    static void printFloatLeft(char * str,int size,int integer,byte decimalPosition);
};

#endif 