#include "BaseTiempoDS1307.hpp"
#include "EI2C1.h"


/*Registros de tiempo*/
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
    bool CH:1;
  }bits;
  byte _byte;
}SecondsRegister;

typedef struct{
  SecondsRegister seconds;
  MinutesRegister minutes;
  HoursRegister hours;  
}TimeRegisters;

/*Registros de Fecha*/
typedef union{
  struct{
    byte dayLow:4;
    byte dayHigh:2;
  }bits;
  byte _byte;
}DaysRegister;

typedef union{
  struct{
    byte monthLow:4;
    byte monthHigh:1;
  }bits;
  byte _byte;
}MonthsRegister;

typedef union{
  struct{
    byte yearLow:4;
    byte yearHigh:4;
  }bits;
  byte _byte;
}YearRegister;

typedef struct{
  DaysRegister days;
  MonthsRegister months;
  YearRegister years;
}DateRegister;


/*
** ===================================================================
**     Method      :  BaseTiempoDS1307_constructor (bean TimeDate)
**
**     Description :
** ===================================================================
*/
BaseTiempoDS1307::BaseTiempoDS1307()
{

  struct  {
    byte address;
    TimeRegisters time;
  }tiempoEnviar;
  
  word w;
  bool cambiado = FALSE;
  
  EI2C1_Init();
  
  EI2C1_SendChar(0);  // me posiciono en las horas
  EI2C1_SendStop();
  EI2C1_RecvBlock(&tiempoEnviar.time,sizeof(tiempoEnviar.time),&w);
  EI2C1_SendStop();
  if(tiempoEnviar.time.hours.bits.amPm){    //Esta configurado como ampm?
    tiempoEnviar.time.hours.bits.amPm = FALSE; 
    cambiado = TRUE;
  }
  if(tiempoEnviar.time.seconds.bits.CH){
    tiempoEnviar.time.seconds.bits.CH = FALSE;
    cambiado = TRUE;
  }
  
  if(cambiado){
    tiempoEnviar.address=0;
    EI2C1_SendBlock(&tiempoEnviar,sizeof(tiempoEnviar),&w);  
    EI2C1_SendStop();
  }
  
  
}


/*
** ===================================================================
**     Method      :  BaseTiempoDS1307_setTiempo
** ===================================================================
*/
void BaseTiempoDS1307::setTiempoValidado(byte horas,byte min,byte segs){

  struct  {
    byte address;
    TimeRegisters time;
  }timeEnviar;

  word enviados;
  
  timeEnviar.address=0;
  
  timeEnviar.time.hours.bits.hourHigh = horas /10;
  timeEnviar.time.hours.bits.hourLow  = horas %10;
  timeEnviar.time.hours.bits.amPm=FALSE;
  
  timeEnviar.time.minutes.bits.minHigh = min/10;
  timeEnviar.time.minutes.bits.minLow = min%10;
  
  timeEnviar.time.seconds.bits.secHigh = segs / 10; 
  timeEnviar.time.seconds.bits.secLow = segs % 10;
  timeEnviar.time.seconds.bits.CH=FALSE;
  
  EI2C1_SendBlock(&timeEnviar,sizeof(timeEnviar),&enviados);
  EI2C1_SendStop();
  
}

/*
** ===================================================================
**     Method      :  BaseTiempoDS1307_getTiempo
** ===================================================================
*/

void BaseTiempoDS1307::getTiempo(TIMEREC *time){
  TimeRegisters timeRecivido;
  word recibidos;
  
  EI2C1_SendChar(0);  // me posiciono en los segundos
  EI2C1_SendStop();
  EI2C1_RecvBlock(&timeRecivido,sizeof(timeRecivido),&recibidos);
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
void BaseTiempoDS1307::setFechaValidada(word year,byte month,byte day){
  
  struct  {
    byte address;
    DateRegister date;
  }fechaEnviar;
 
  word enviados;
  byte err;
   
  fechaEnviar.address=4;
  
  year -= 2000; 
  fechaEnviar.date.years.bits.yearHigh = year /10;
  fechaEnviar.date.years.bits.yearLow  = year %10;
  
  fechaEnviar.date.months.bits.monthHigh = month/10;
  fechaEnviar.date.months.bits.monthLow = month%10;
  
  fechaEnviar.date.days.bits.dayHigh = day / 10; 
  fechaEnviar.date.days.bits.dayLow = day % 10;  

  err=EI2C1_SendBlock(&fechaEnviar,sizeof(fechaEnviar),&enviados);
  EI2C1_SendStop();  
  //modificar, error
}

/*
** ===================================================================
**     Method      :  BaseTiempoDS1307_getFechaValidada
** ===================================================================
*/
void BaseTiempoDS1307::getFecha(DATEREC *date){
  DateRegister fechaRecivida;

  word recibidos;
  
  EI2C1_SendChar(4);  // me posiciono en los dias
  EI2C1_SendStop();
  EI2C1_RecvBlock(&fechaRecivida,sizeof(fechaRecivida),&recibidos);
  EI2C1_SendStop();
  date->Year= 2000+fechaRecivida.years.bits.yearHigh * 10 + fechaRecivida.years.bits.yearLow;
  date->Month = fechaRecivida.months.bits.monthHigh * 10 + fechaRecivida.months.bits.monthLow;
  date->Day = fechaRecivida.days.bits.dayHigh * 10 + fechaRecivida.days.bits.dayLow;
  
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
**     Method      :  BaseTiempoDS1307_getConfigurado
**
**     Description :
** ===================================================================
*/
/*bool BaseTiempoDS1307_getConfigurado(void * _self){
  struct BaseTiempoDS1307 * self = _self;
  return TRUE;
}
  */
