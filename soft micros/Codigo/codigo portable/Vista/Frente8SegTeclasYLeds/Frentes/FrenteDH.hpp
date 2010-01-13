#ifndef _FRENTE_DH_HPP
#define _FRENTE_DH_HPP

#include "Vista/Frente8SegTeclasYLeds/FrenteCustom.hpp"


class FrenteDH:public FrenteCustom{
  public:
    FrenteDH* getInstancia();
    virtual Display* getDisplay(byte numDisplay);
  protected:
    FrenteDH();
    virtual void seleccionarDigito(byte barrido);
    virtual void encenderLeds(byte leds);
    virtual bool isTeclaPresionada();
    virtual byte getTecla(byte barrido);
  private:
    Display displays[CANTIDAD_DISPLAYS];
};


#endif