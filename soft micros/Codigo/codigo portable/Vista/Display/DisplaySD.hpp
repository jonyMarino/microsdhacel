#ifndef _DISPLAY_SD_HPP
#define _DISPLAY_SD_HPP

#include <stdtypes.h>
#include "PE/include/PE_Types.h"
#include "OOC/ooc/lib_cpp/OutputStream.hpp"

#define  MAX_MENSAJE 30
/*maneja un display y lo imprime por el puerto dado*/
class DisplaySD:public OutputStream{
  public:
    DisplaySD(byte*puerto,char _nroDys);
    void write(const char* str);
    //void writeByte(unsigned char b);
    void write(int i);
    void writeAsFloat(int i,uchar decimales);
    void borrar();
    bool isScrolling();
    void apagar();
    
  private:
    byte corrimiento;
    byte nLetras;
    byte * puerto;
    char mensaje[MAX_MENSAJE]; //esta guardado en 8 segmentos
    char nroDys;
    
    void resetearCorrimiento();
    void incrementarCorrimiento();
    void imprimirDigito(byte numDigito);
    friend class FrenteCustomSD;   
};

#endif
