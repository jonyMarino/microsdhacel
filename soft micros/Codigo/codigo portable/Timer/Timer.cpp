#include "Timer.hpp"

#include "stddef.h"
#include "stdtypes.h"
#include "Cpu.h"
#include "BaseTimers_1ms_40ms.hpp"

#pragma DATA_SEG Timer_DATA                                            
#pragma CODE_SEG Timer_CODE 
#pragma CONST_SEG DEFAULT


/*
** ===================================================================
**     Method      :  Timer_Construct 
**    Description : Metodo para setear los 
**                  valores de configuración del contador
** ===================================================================
*/
Timer::Timer(ulong tiempo){
  BaseTimers * baseTimer = BaseTimers_1ms_40ms::getInstance(); 
  ulong cuenta = baseTimer->getCuenta();
  this->baseTimer = baseTimer;
  this->tiempo= tiempo;
  this->next_cuenta=cuenta+tiempo;
  
  if(cuenta >= this->next_cuenta)
    this->of=TRUE;  
  else
    this->of=FALSE;
    
  baseTimer->add(this);

}



/*
** ===================================================================
**     Method      :  Timer_Destruct 
**    Description : Metodo para destruir el Timer
** ===================================================================
*/
Timer::~Timer(){
  stop();
}

/*
** ===================================================================
**     Method      :  setBaseTimer 
**    Description : setea la entrada de ticks del timer
** ===================================================================
*/
void Timer::setBaseTimer(BaseTimers * base){ 
  baseTimer = base;
}
/*
** ===================================================================
**     Method      :  Timer_OnTime 
**    Description : Evento al llegar al tiempo fijado
** ===================================================================
*/
void Timer::onTime(){
  stop();
}

/*
** ===================================================================
**     Method      :  comparar 
**    Description : 
** ===================================================================
*/
void Timer::comparar(){  
  bool comp;
  BaseTimers * baseTimer = this->baseTimer;  
  ulong cuentaTmp = baseTimer->getCuenta();
  ulong nextCuentaTmp = this->next_cuenta;
  ulong tiempoTmp = this->tiempo;
  
  if(this->of)
    comp= cuentaTmp <= nextCuentaTmp;
  else
    comp= cuentaTmp >= nextCuentaTmp;
  
  if (comp ){
    int error = cuentaTmp - nextCuentaTmp;
    error = (error<0)?-error:error;
    nextCuentaTmp +=   error + tiempoTmp;
    this->next_cuenta=nextCuentaTmp;    
    if(cuentaTmp >= nextCuentaTmp){
      this->of=TRUE;        
    }
    onTime();
  }
}

/*
** ===================================================================
**     Method      :  Timer_getCuenta 
**    Description : Regresa la cuenta actual que se resetea al llegar al tiempo
** ===================================================================
*/
ulong Timer::getCuenta(){
  ulong cuentaTmp;
  ulong nextCuentaTmp;
  ulong tiempoTmp;
  
  if(isFinished())
    return 0;
  cuentaTmp = this->baseTimer->getCuenta();

  Cpu_DisableInt();
    nextCuentaTmp = this->next_cuenta;
    tiempoTmp = this->tiempo;
  Cpu_EnableInt();
   
  return cuentaTmp - (nextCuentaTmp - tiempoTmp);
}

/*
** ===================================================================
**     Method      :  Timer_isfinish 
**    Description : Indica si ya termino la cuenta
** ===================================================================
*/
uchar Timer::isFinished(){
  if(this->baseTimer)
    return !this->baseTimer->contains(this);
  return TRUE;
}

/*
** ===================================================================
**     Method      :  Timer_Restart 
**    Description : Reinicia la cuenta del tiempo
** ===================================================================
*/
void Timer::restart(){
  ulong cuenta = this->baseTimer->getCuenta();
  this->next_cuenta= cuenta + this->tiempo ;
  if(cuenta >= this->next_cuenta)
    this->of=TRUE;  
  else
    this->of=FALSE;
  if(isFinished())
    baseTimer->add(this);
}

/*
** ===================================================================
**     Method      :  Timer_setTime 
**    Description : Setea un tiempo nuevo y reinicia la cuenta del tiempo
** ===================================================================
*/
void Timer::setTime(ulong tiempo){					 
  this->tiempo=tiempo;
  restart();
}

/*
** ===================================================================
**     Method      :  Timer_getTime 
**    Description : Obtiene el tiempo a alcanzar
** ===================================================================
*/
ulong Timer::getTime(){
  return tiempo;
}

/*
** ===================================================================
**     Method      :  Timer_Stop 
**    Description : Detiene la cuenta del timer
** ===================================================================
*/
void Timer::stop(){  
  baseTimer->moveOut(this);
}



#pragma CODE_SEG Timer_CODE

