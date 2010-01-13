#ifndef _FRENTE_CUSTOM_HPP
#define _FRENTE_CUSTOM_HPP


#include "Display/Display.hpp"
#include "Timer/FlagTimer/FlagTimer.hpp"
#include "Teclas.hpp"
#include "PE_Types.h"

#define CANTIDAD_VALIDACIONES 8

class FrenteCustom{
  public:
    FrenteCustom * getInstancia();
    virtual Display* getDisplay(byte numDisplay)=0;
    void setLed(bool val,byte num); 
    void borrar(void);  
  protected:
    virtual void on1ms();
    FrenteCustom();
    virtual void seleccionarDigito(byte barrido)=0;
    virtual void encenderLeds(byte leds)=0;
    virtual bool isTeclaPresionada()=0;
    virtual byte getTecla(byte barrido)=0;
  private:   
    FlagTimer scrollTimer;
    Teclas teclas;
    byte leds;              // indica los leds que fueron presionados
    byte barrido;           // contador de la etapa de barrido actual (0-DIGITOS*DISPLAYS)
    byte barridoTeclas;     // contador del barrido de teclas (0-CANTIDAD_TECLAS-1)
    byte teclasPresionadas; // registro donde se van guardando las teclas presionadas en un barrido
    byte posiblesTeclas;      // conjunto de teclas presionadas en un barrido posiblemente validas
    byte debounce;          // contador del numero de entradas iguales hasta aceptar la tecla
    void actualizarTeclas();
    void resetScroll();   
};

#endif
