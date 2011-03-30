#ifndef _LEDS_SALIDA_HPP
#define _LEDS_SALIDA_HPP

#include "PE/include/PE_Types.h"
#include "OOC/util/lib_cpp/Array.h"
#include "Vista/Frente8SegTeclasYLeds/FrenteCustom.hpp"

// enciende o apaga "ledNum" de acuerdo al valor en el bit (o operacion) "(*addr)&mask"
// el encendido/ apagado se ejecuta en un thread
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