#ifndef _LEDS_SALIDA_HPP
#define _LEDS_SALIDA_HPP

#include "PE_Types.h"
#include "OOC/util/lib_cpp/Array.h"
#include "Vista/Frente8SegTeclasYLeds/FrenteCustom.hpp"

typedef struct{
  byte * addr;
  byte mask;
  byte ledNum;
}LedConfig;

class LedsSalida{
  public:
    typedef struct{
      byte * addr;
      byte mask;
      byte ledNum;
    }LedConfig;

  
    LedsSalida(const struct Array& ,FrenteCustom &);
    
  private:
   FrenteCustom & frente;
   const struct Array& array;
   static void* ledsActualizar(void*);   
};


#endif