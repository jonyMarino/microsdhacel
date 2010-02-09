#ifndef _GETTER_HPP
#define _GETTER_HPP


#include "../../Librerias/OOC/ooc/lib_cpp/OutputStream.hpp"

#pragma DATA_SEG GETTER_DATA                                            
#pragma CODE_SEG GETTER_CODE                     
#pragma CONST_SEG DEFAULT            /* Constant section for this module */


class Getter{
  public:
    virtual void print(OutputStream& os)=0;
    virtual int getVal()=0;
};

#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT                     
#pragma CONST_SEG DEFAULT            /* Constant section for this module */


#endif