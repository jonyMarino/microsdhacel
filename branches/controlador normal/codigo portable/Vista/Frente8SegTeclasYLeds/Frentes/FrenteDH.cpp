#include <assert.h>
#include "FrenteDH.hpp"
#include "Display1.h"
#include "SelectorDigito.h"
#include "PUL.h"


const byte FrenteDH::codigoSelectorDigito[]={
  0x01,0x02,0x04,0x08,  //display superior
  0x10,0x20,0x40,0x80   //display inferior
}; 

const byte FrenteDH::codigoTecla[]={
  0,0x02,0x04,0x08,  //display superior
  0x10,0,0,0   //display inferior
};



FrenteDH * FrenteDH::instancia=NULL;

FrenteDH::FrenteDH():display1(&P_DISPLAY1),display2(&P_DISPLAY1){
}

FrenteDH* FrenteDH::getInstancia(){
  if(!instancia)
    instancia = new FrenteDH();
  return instancia;
}

Display* FrenteDH::getDisplay(byte numDisplay){
  return (numDisplay)?&display1:&display2;
}


void FrenteDH::seleccionarDigito(byte barrido){                                                  
  assert(barrido<8);

  SelectorDigito_putVal(codigoSelectorDigito[barrido]);
}

void FrenteDH::encenderLeds(byte leds){
  P_DISPLAY1 = 0;
  SelectorDigito_putVal(leds|0x80);
}

bool FrenteDH::isTeclaPresionada(){
  return !PUL_GetVal();
}

byte FrenteDH::getTeclaPosicion(byte barrido){
  return  codigoTecla[barrido];
}


