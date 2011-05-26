#include <stdio.h>
#include "IAdc.hpp"
#include "Adc.hpp"
#include "ADC1.h"
#include "ADC.h"
#include "TI1.h"
#include "OOC/ooc/lib_cpp/OutputStream.hpp"

#define _TIEMPO_AD_EN_MILISEGUNDOS 1000
const int AD_CONVERTING_TIME =_TIEMPO_AD_EN_MILISEGUNDOS-TIEMPO_GRABACION; 
const int ADTIME = _TIEMPO_AD_EN_MILISEGUNDOS;
bool Adc::init=FALSE;
MethodTimer *Adc::timerPeriodo=NULL;



void start(void * a){
  ADC_Start();  
}

const struct Method Adc::onPeriodo={
start,NULL
};

Adc::Adc(int _pin):pin(_pin) {
  if(!init){
    init = TRUE;
    ADC1_Init();
    ADC_Start();  //Inicia el ADC 
    //onPeriodo.pMethod =  start;
    //onPeriodo.obj = this;
    timerPeriodo= new MethodTimer(ADTIME,onPeriodo); //cada  ADTIME se va a ejecutar una nueva medición
  }
}

bool Adc::isNewVal() {
  return ADC_isread(pin);
}

IAdc::AD_State Adc::getState() {
  if(timerPeriodo->getCuenta()>AD_CONVERTING_TIME)
    return AD_WAITING;
  else
    return AD_CONVERTING;
}

int Adc::getVal() {
  return ADC_getVal(pin);  
}

void Adc::print(OutputStream& os){
 // os.write(getVal());
}

int Adc::getTemperaturaAmbiente(){
  return ADC_getTA();
}



