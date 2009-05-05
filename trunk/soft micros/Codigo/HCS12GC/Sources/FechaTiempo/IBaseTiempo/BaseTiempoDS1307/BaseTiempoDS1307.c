#include "BaseTiempoDS1307.h"
#include "EI2C1.h"



void BaseTiempoDS1307_defConstructor(void * self,va_list * args);
void BaseTiempoDS1307_getTiempo(void * self,TIMEREC *time);
byte BaseTiempoDS1307_setTiempoValidado(void * _self,byte horas,byte min,byte segs);
void BaseTiempoDS1307_getFecha(void * self,DATEREC *date);
byte BaseTiempoDS1307_setFechaValidada(void * self,word year,byte month,byte day);
bool BaseTiempoDS1307_getConfigurado(void * _self);

const struct IBaseTiempoClass BaseTiempoDS1307 = {
    I_BASE_TIEMPO_CLASS_INITIALIZATION(IBaseTiempoClass,
                             BaseTiempoDS1307,  
                             IBaseTiempo,
                             BaseTiempoDS1307_defConstructor,
                             Object_dtor,
                             Object_differ,
                             Object_puto,
                             BaseTiempoDS1307_getTiempo,
                             BaseTiempoDS1307_setTiempoValidado,
                             BaseTiempoDS1307_getFecha,
                             BaseTiempoDS1307_setFechaValidada,
                             BaseTiempoDS1307_getConfigurado
                             )  
};


typedef union{
  struct{
    byte hourLow:4;
    byte hourHigh:2;
    bool amPm:1;
  }bits;
  byte _byte;
}HoursRegister;

typedef union{
  struct{
    byte minLow:4;
    byte minHigh:3;
  }bits;
  byte _byte;
}MinutesRegister;

typedef union{
  struct{
    byte secLow:4;
    byte secHigh:3;
  }bits;
  byte _byte;
}SecondsRegister;

typedef struct{
  SecondsRegister seconds;
  MinutesRegister minutes;
  HoursRegister hours;  
}TimeRegisters;
/*
** ===================================================================
**     Method      :  BaseTiempoDS1307_constructor (bean TimeDate)
**
**     Description :
** ===================================================================
*/
void BaseTiempoDS1307_constructor(void * _self)
{
  struct BaseTiempoDS1307 * self = _self;
  HoursRegister h;
  
  EI2C1_SendChar(2);  // me posiciono en las horas
  EI2C1_RecvChar(&h);
  if(h.bits.amPm){    //Esta configurado como ampm?
    h.bits.amPm = FALSE;
    EI2C1_SendChar(h);
  }
  
  EI2C1_SendStop();
}
/*
** ===================================================================
**     Method      :  TmDt1_DefConstructor (bean TimeDate)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/
void BaseTiempoDS1307_defConstructor(void * self,va_list * args){
  BaseTiempoDS1307_constructor(self);  
}

/*
** ===================================================================
**     Method      :  BaseTiempoDS1307_setTiempo
** ===================================================================
*/
byte BaseTiempoDS1307_setTiempoValidado(void * _self,byte horas,byte min,byte segs){
  struct BaseTiempoDS1307 * self = _self;
  TimeRegisters timeEnviar;
  word enviados;
  
  timeEnviar.hours.bits.hourHigh = horas /10;
  timeEnviar.hours.bits.hourLow  = horas %10;
  
  timeEnviar.minutes.bits.minHigh = min/10;
  timeEnviar.minutes.bits.minLow = min%10;
  
  timeEnviar.seconds.bits.secHigh = segs / 10; 
  timeEnviar.seconds.bits.secLow = segs % 10;
  
  EI2C1_SendChar(0);  // me posiciono en los segundos
  EI2C1_RecvBlock(&timeEnviar,3,&enviados);
  EI2C1_SendStop();
  
}

/*
** ===================================================================
**     Method      :  BaseTiempoDS1307_getTiempo
** ===================================================================
*/
void BaseTiempoDS1307_getTiempo(void * self,TIMEREC *time){
  TimeRegisters timeRecivido;
  word recibidos;
  
  EI2C1_SendChar(0);  // me posiciono en los segundos
  EI2C1_RecvBlock(&timeRecivido,3,&recibidos);
  EI2C1_SendStop();
  time->Hour= timeRecivido.hours.bits.hourHigh * 10 + timeRecivido.hours.bits.hourLow;
  time->Min = timeRecivido.minutes.bits.minHigh * 10 + timeRecivido.minutes.bits.minLow;
  time->Sec = timeRecivido.seconds.bits.secHigh * 10 + timeRecivido.seconds.bits.secLow;
}

/*
** ===================================================================
**     Method      :  BaseTiempoDS1307_setFechaValidada
** ===================================================================
*/
byte BaseTiempoDS1307_setFechaValidada(void * self,word year,byte month,byte day){
  
}

/*
** ===================================================================
**     Method      :  BaseTiempoDS1307_getFechaValidada
** ===================================================================
*/
void BaseTiempoDS1307_getFecha(void * self,DATEREC *date){
  date->Day=3;
  date->Month=5;
  date->Year=2009;  
}
/*
** ===================================================================
**     Method      :  EI2C1_OnNACK
** ===================================================================
*/
void EI2C1_OnNACK(void){

}

/*
** ===================================================================
**     Method      :  EI2C1_OnTxChar
** ===================================================================
*/
void EI2C1_OnTxChar(void){

}

/*
** ===================================================================
**     Method      :  EI2C1_OnRxChar
** ===================================================================
*/
void EI2C1_OnRxChar(void){

}

/*
** ===================================================================
**     Method      :  BTFechaPersistente_incUnSegundo
**
**     Description :
** ===================================================================
*/
bool BaseTiempoDS1307_getConfigurado(void * _self){
  struct BaseTiempoDS1307 * self = _self;
  return TRUE;
}

