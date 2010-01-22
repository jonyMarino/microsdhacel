#ifndef _MANEJADOR_MEMORIA_HPP
#define _MANEJADOR_MEMORIA_HPP


#include "Timer/Timer.hpp"
#include "PE/include/PE_Types.h"
#include "PE/include/PE_Error.h"
#include "Memoria/FshTypeSizes.h"


class ManejadorMemoria{
  public:
    virtual fbyte getByte(fbyte*)=0;
    virtual byte setByte(fbyte*,fbyte)=0;  
    virtual word getWord(word*)=0;
    virtual byte setWord(word*,word)=0; 
    //virtual dword getDWord(dword*)=0; 
    //virtual byte setDWord(dword*,dword)=0;    

};

#endif
