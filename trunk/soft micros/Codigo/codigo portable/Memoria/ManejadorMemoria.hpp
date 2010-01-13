#ifndef _MANEJADOR_MEMORIA_HPP
#define _MANEJADOR_MEMORIA_HPP


#include "Timer.hpp"
#include "PE_Types.h"
#include "PE_Error.h"
#include "FshTypeSizes.h"


class ManejadorMemoria{
  public:
    virtual fbyte getByte(void*,fbyte*);
    virtual byte setByte(void*,fbyte*,fbyte);  
    virtual word getWord(void*,word*);
    virtual byte setWord(void*,word*,word); 
    virtual dword getDWord(void*,dword*); 
    virtual byte setDWord(void*,dword*,dword);    

};

#endif
