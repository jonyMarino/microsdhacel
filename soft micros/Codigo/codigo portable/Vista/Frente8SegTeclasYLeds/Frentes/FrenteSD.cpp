#include <assert.h>
#include "FrenteSD.hpp"
#include "Display1.h"
#include "Display2.h"
#include "SelectorDigito.h"
#include "PUL.h"


const byte FrenteSD::codigoSelectorDigito[]={
  0x10,0x20,0x40,0x80,  //display superior
  0x01,0x02,0x04,0x08,   //display inferior
  
    
}; 

const byte FrenteSD::codigoTecla[]={
  
  0x01,0x02,0x04,0x08,  //display inferior
  0x10,0x20,0x40,0x80,  //display superior
};

FrenteSD * FrenteSD::instancia=NULL;

FrenteSD::FrenteSD():display1(&P_DISPLAY1,1),display2(&P_DISPLAY1,2),display3(&P_DISPLAY2,3),display4(&P_DISPLAY2,4){
}

FrenteSD* FrenteSD::getInstancia(){
  if(!instancia)
    instancia = new FrenteSD();
  return instancia;
}

DisplaySD* FrenteSD::getDisplay(byte numDisplay){
  switch (numDisplay){
    case 0:return &display1;break;
    case 1:return &display2;break;
    case 2:return &display3;break;
    case 3:return &display4;break;
  }
}


void FrenteSD::seleccionarDigito(byte barrido){                                                  
  assert(barrido<8);

  SelectorDigito_putVal(codigoSelectorDigito[barrido]);
}

void FrenteSD::encenderLeds(byte leds){
  P_DISPLAY1 = 0;
  P_DISPLAY2 = 0;
  SelectorDigito_putVal(leds|0x80);
}

bool FrenteSD::isTeclaPresionada(){
  return !PUL_GetVal();
}

byte FrenteSD::getTeclaPosicion(byte barrido){
  return  codigoTecla[barrido];
}
