#ifndef _FRENTE_SD_HPP
#define _FRENTE_SD_HPP

#include "Vista/Frente8SegTeclasYLeds/FrenteCustomSD.hpp"

#define CANTIDAD_DISPLAYS 4

class FrenteSD:public FrenteCustomSD{
  public:
    static FrenteSD* getInstancia();
    virtual DisplaySD* getDisplay(byte numDisplay);
  protected:
    FrenteSD();
    virtual void seleccionarDigito(byte barrido);
    virtual void encenderLeds(byte leds);
    virtual bool isTeclaPresionada();
    virtual byte getTeclaPosicion(byte barrido);
  private:
    DisplaySD display1;
    DisplaySD display2;
    DisplaySD display3;
    DisplaySD display4;
    static const byte codigoSelectorDigito[16];
    static const byte codigoTecla[16];
    static FrenteSD * instancia;
    
};


#endif