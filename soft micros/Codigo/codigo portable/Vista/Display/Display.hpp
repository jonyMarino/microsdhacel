#ifndef _DISPLAY_HPP
#define _DISPLAY_HPP

#include <stdtypes.h>
#include "PE/include/PE_Types.h"
#include "OOC/ooc/lib_cpp/OutputStream.hpp"

#define  MAX_MENSAJE 30
/*maneja un display y lo imprime por el puerto dado*/
class Display:public OutputStream{
  public:
    Display(byte*puerto);
    void write(const char* str);
    //void writeByte(unsigned char b);
    void write(int i);
    void writeAsFloat(int i,uchar decimales);
    void borrar();
    bool isScrolling();
    void apagar();
    
    void resetearCorrimiento();
    void incrementarCorrimiento();
    void imprimirDigito(byte numDigito);
  
    char mensaje[MAX_MENSAJE]; //esta guardado en 8 segmentos
  private:
    byte corrimiento;
    byte nLetras;
    byte * puerto;
    
    
    friend class FrenteCustom;   
};

#endif
