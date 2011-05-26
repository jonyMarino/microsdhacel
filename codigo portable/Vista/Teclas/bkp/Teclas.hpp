#ifndef _TECLAS_HPP
#define _TECLAS_HPP

#include "PE/include/PE_Types.h"
#include "Timer/RlxMTimer/RlxMTimer.hpp"

class Teclas{
  public:
    Teclas();
    void presionar(byte teclas);
    byte getTecla();
    bool isTimePass();
  private:
    RlxMTimer * timerChequeo;   //cambiar: por Method que no puedo llamar al constructor
    byte  teclasPresionadas; 
    long  contadorTimePass;
    byte	teclas;					        // tecla presionada. NULL: teclas liberadas
    byte	teclaAnterior;					// estado anterior
    byte  teclaAnteriorTmp;
    byte	rampa;				          // valor de recarga para ir acelerando
    byte	tecla;				          // tecla presionada a devolver.
    byte	contadorRampa;					// contador para generar el tiempo entre repeticiones
    void  resetTimePass();
    void  chequear();
    static void staticChequear(void*self);
};

#endif 