#ifndef _FRENTE_SD_HPP
#define _FRENTE_SD_HPP

#include "Vista/Frente8SegTeclasYLeds/FrenteCustom.hpp"

#define CANTIDAD_DISPLAYS 4

class FrenteSD:public FrenteCustom{
  public:
    static FrenteSD* getInstancia();
    virtual Display* getDisplay(byte numDisplay);
  protected:
    FrenteSD();
    virtual void seleccionarDigito(byte barrido);
    virtual void encenderLeds(byte leds);
    virtual bool isTeclaPresionada();
    virtual byte getTeclaPosicion(byte barrido);
  private:
    Display display1;
    Display display2;
    Display display3;
    Display display4;
    static const byte codigoSelectorDigito[8];
    static const byte codigoTecla[8];
    static FrenteSD * instancia;
    
};


#endif