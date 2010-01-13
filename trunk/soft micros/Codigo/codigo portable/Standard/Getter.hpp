#ifndef _GETTER_HPP
#define _GETTER_HPP


#include "../../Librerias/OOC/ooc/lib_cpp/OutputStream.hpp"

class Getter{
  public:
    virtual void print(OutputStream& os)=0;
    virtual int getVal()=0;
};

#endif