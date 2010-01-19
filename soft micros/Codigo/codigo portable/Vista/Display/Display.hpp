#ifndef _DISPLAY_HPP
#define _DISPLAY_HPP

#include "PE/include/PE_Types.h"
#include "OOC/ooc/lib_cpp/OutputStream.hpp"

#define  MAX_MENSAJE 30
/*maneja un display y lo imprime por el puerto dado*/
class Display:public OutputStream{
  public:
    Display(byte*puerto);
    void write(const char* str);
    void write(unsigned char b);
    void borrar();
    bool isScrolling();
    void apagar();
    
  private:
    byte corrimiento;
    byte nLetras;
    byte * puerto;
    char mensaje[MAX_MENSAJE]; //esta guardado en 8 segmentos
    
    void resetearCorrimiento();
    void incrementarCorrimiento();
    void imprimirDigito(byte numDigito);
    friend class FrenteCustom;   
};

#endif
