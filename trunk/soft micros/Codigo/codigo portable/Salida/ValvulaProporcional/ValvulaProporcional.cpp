
#include "ValvulaProporcional.hpp"

#define  MAX_TIEMPOABIERTO 10000
#define  MAX_BANDAMUERTA   10000
#define  FACTOR_SEGURIDAD  1

void ValvulaProporcional::onCheckear()
{
  //cada 10ms es llamada 
  
  word timesOpenClose,timesMuerto;
  word potencia_vp = Salida_getPotencia();
  if((timeCloseInit)>0){
    (timeCloseInit)--;
    cerrar(self);  // inicio cerrando durante el tiempo "timeCloseInit"
    return;
  } else if(potencia_vp == 1000)
            abrir(self);
         else if(potencia_vp == 0)
            detener(self);
               else{
                 timesOpenClose=potencia_vp*(conf->tiempoAbierto);  //tiempo en milisegundos
                 timesMuerto=(conf->bandaMuerta)*1000;
                 if((timesOpenClose>(timeActual))) {
                  abrir();
                  timeActual = (timeActual + 10);
                 }
                 else if((timesOpenClose<(timeActual))) {
                        cerrar();
                        timeActual = (timeActual - 10);
                 }
                       else
                        detener(); 
               }
               if((timesOpenClose==timeActual)||(timesOpenClose<(timeActual+timesMuerto))||(timesOpenClose>(timeActual-timesMuerto)))
                 detener(); 
               
}
  
}

unsigned int ValvulaProporcional::getTiempoAbierto() {
  return _MANEJADOR_MEMORIA_GET_WORD(manejadorMemoria,conf->tiempoAbierto);
}

unsigned char ValvulaProporcional::setTiempoAbierto(unsigned int value) {
  return _MANEJADOR_MEMORIA_SET_WORD(manejadorMemoria,conf->tiempoAbierto,(uchar)value);
}

unsigned int ValvulaProporcional::getBandaMuerta() {
  return _MANEJADOR_MEMORIA_GET_WORD(manejadorMemoria,conf->bandaMuerta);
}

unsigned char ValvulaProporcional::setBandaMuerta(unsigned int value) {
  return _MANEJADOR_MEMORIA_SET_WORD(manejadorMemoria,conf->bandaMuerta,value);
}

unsigned int ValvulaProporcional::getLimiteSuperiorTiempoAbierto()
{
  return MAX_TIEMPOABIERTO;
}

unsigned int ValvulaProporcional::getLimiteSuperiorBandaMuerta()
{
  return MAX_BANDAMUERTA;
}

unsigned int ValvulaProporcional::getPotencia()
{
  unsigned int potenciaActual;
  potenciaActual = (self->timeActual)/(self->conf->tiempoAbierto); // ya que timeActual esta en miliseg y tiempoAbierto en seg, no multiplico por 1000
  
  return potenciaActual;
}

ValvulaProporcional::setPotencia(unsigned int potencia) 
{
 Salida_setPotencia(potencia);
}

TipoSalida ValvulaProporcional::getTipoSalida() 
{
  return SALIDA_PROPORCIONAL;
}

void ValvulaProporcional::setTipoSalida(TipoSalida tipoSalida) 
{
  return;
}

void ValvulaProporcional::cerrar() 
{
  clrReg8Bits(*(puertoApertura),(mascaraApertura));                           
  setReg8Bits(*(puertoCierre), (mascaraCierre));
}

void ValvulaProporcional::abrir() 
{
  clrReg8Bits(*(puertoCierre),(mascaraCierre));                           
  setReg8Bits(*(puertoApertura),(mascaraApertura));
}

void ValvulaProporcional::detener() 
{
  clrReg8Bits(*(puertoCierre), (mascaraCierre));                           
  clrReg8Bits(*(puertoApertura),(mascaraApertura));
}

