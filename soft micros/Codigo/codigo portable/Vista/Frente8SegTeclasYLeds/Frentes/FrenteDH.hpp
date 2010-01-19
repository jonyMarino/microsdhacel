#ifndef _FRENTE_DH_HPP
#define _FRENTE_DH_HPP

#include "Vista/Frente8SegTeclasYLeds/FrenteCustom.hpp"

#define CANTIDAD_DISPLAYS 2

class FrenteDH:public FrenteCustom{
  public:
    static FrenteDH* getInstancia();
    virtual Display* getDisplay(byte numDisplay);
  protected:
    FrenteDH();
    virtual void seleccionarDigito(byte barrido);
    virtual void encenderLeds(byte leds);
    virtual bool isTeclaPresionada();
    virtual byte getTeclaPosicion(byte barrido);
  private:
    Display display1;
    Display display2;
    static const byte codigoSelectorDigito[8];
    static const byte codigoTecla[8];
    static FrenteDH * instancia;
    
};


#endif