#ifndef _LEDS_SALIDA_SD_HPP
#define _LEDS_SALIDA_SD_HPP

#include "PE_Types.h"
#include "OOC/util/lib_cpp/Array.h"
#include "Vista/Frente8SegTeclasYLeds/FrenteCustomSD.hpp"


class LedsSalidaSD{
  public:
    typedef struct{
      byte * addr;
      byte mask;
      byte ledNum;
    }LedConfig;

  
   LedsSalidaSD(const struct Array& ,FrenteCustomSD &);
      
  private:
   FrenteCustomSD & frente;
   const struct Array& array;
   static void* ledsActualizar(void*);   
};


#endif