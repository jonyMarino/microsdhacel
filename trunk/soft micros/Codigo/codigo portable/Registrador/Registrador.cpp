/*  MODULE:Registrador. 
**     Filename  : Registrador.C
**     Project   : Registrador
**     Processor : MC9S12GC32CFU16
**     Version   : 0.0.2
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 19/03/2008, 11:59
**     Abstract  :
**           Guarda los datos de los serializables
*/

#include <assert.h>
#include <stdlib.h>
#include "Registrador.hpp"
#include "System.hpp"


/*
void onDateTimeChange(void * _self){
  Registrador * self = _self;
  self->stop();
}
  */
/*
** ===================================================================
**     Method      :  Adq_Constructor 
**    Description  :  Constructor del Objeto
** ===================================================================
*/
Registrador::Registrador(const struct Array& _serializables,ConfiguracionRegistrador& _configuracion):serializables(_serializables),configuracion(_configuracion),serializables(_serializables),configuracion(_configuracion),timer(_configuracion.getIntervalo()*1000,onTime,this){
  assert(Array_count(&serializables)>0);
  
  timer.stop();
  grabando = FALSE;  
  
	
	if (configuracion.getAdquirir()==TRUE) {		 // la adquisicion quedo en si al apagarse el equipo?								  
	  #ifdef DS1307
	  start();
	  #else
	  estado = HULT;
	  configuracion.setAdquirir(FALSE);		 // Poner la adquisicion en no
    #endif
  }else
    estado = NO;  //no

}

/*
** ===================================================================
**     Method      :  Registrador::onTime 
**    Type:        :  Private
**    Description  :  Funcion que se llama pasado el intervalo
** ===================================================================
*/
void Registrador::onTime(void * _self){
  Registrador * self = (Registrador *)_self;
  
  if (self->estado==SI){
    self->grabando = TRUE;
    self->registrar();
    self->grabando = FALSE;
  }

}

/*
** ===================================================================
**     Method      :  isTimeSet
**    Description  :  indica si se introdujo el tiempo
** ===================================================================
*/
//bool Registrador::isTimeSet(){  
//  return isConfigurado(&System::baseTiempo);   
//}

/*
** ===================================================================
**     Method      :  setEstado
**    Description  :  Prepara el Registrador para el estado propuesto
** ===================================================================
*/
void Registrador::setEstado(Estado estadoProximo){
  if(estado!=SI && estadoProximo==SI)
    timer.setTime(getIntervalo()*1000);
  else
    timer.stop();
  estado=estadoProximo;
  configuracion.setAdquirir(estado);
  
}

/*
** ===================================================================
**     Method      :  setEstado
**    Description  :  Prepara el Registrador para el estado propuesto
** ===================================================================
*/
Registrador::Estado Registrador::getEstado(){
  return estado;
  
}

/*
** ===================================================================
**     Method      :  Adq_Start
**    Description  :  Empieza la adquisicion (si es que la memoria no
**                    se encuentra en full)
** ===================================================================
*/
void Registrador::start(){
  if(getEstado() == FULL){
    return;
  }
  if(getEstado() != SI){        
    setEstado(SI);
  }
}

/*
** ===================================================================
**     Method      :  Adq_Stop 
**    Description  :  Detiene la adquisicion
** ===================================================================
*/
void Registrador::stop(){
  if( getEstado() == SI ){
    setEstado(NO);
  }
}


/*
** ===================================================================
**     Method      :  setAdquirir
**    Description  :  Setea el estado del adquisidor (NO/SI)
** ===================================================================
*/
void  Registrador::setAdquirir(bool val){  
  if(val==FALSE){
    stop();
  }else{
    start();
  }
}

/*
** ===================================================================
**     Method      :  Adq_setIntervalo
**    Description  :  Setea el intervalo de muestreo
** ===================================================================
*/
void Registrador::setIntervalo(int val){  
  configuracion.setIntervalo(val);
  timer.setTime(val*1000);
}


/*
** ===================================================================
**     Method      :  Adq_getIntervalo
**    Description  :  Obtiene el intervalo de muestreo
** ===================================================================
*/
int Registrador::getIntervalo(){
  return configuracion.getIntervalo();
}


/*
** ===================================================================
**     Method      :  Adq_getIntervalo
**    Description  :  Obtiene el intervalo de muestreo
** ===================================================================
*/
const struct Array& Registrador::getSerializables(){
  return serializables;
}

