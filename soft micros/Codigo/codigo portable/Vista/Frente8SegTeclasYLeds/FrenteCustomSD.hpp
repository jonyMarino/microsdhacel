#ifndef _FRENTE_CUSTOM_SD_HPP
#define _FRENTE_CUSTOM_SD_HPP


#include "Vista/Display/DisplaySD.hpp"
#include "Timer/FlagTimer/FlagTimer.hpp"
#include "Vista/Teclas/Teclas.hpp"
#include "PE/include/PE_Types.h"
#include "OOC/lang/reflect/lib_cpp/Method.hpp"
#include "Vista/Frente8SegTeclasYLeds/FrenteCustom.hpp"


class FrenteCustomSD:public FrenteCustom {
  public:
    virtual DisplaySD* getDisplaySD(byte numDisplay)=0;
  protected:
    virtual void on1ms();
    FrenteCustomSD();
  
};

#endif
