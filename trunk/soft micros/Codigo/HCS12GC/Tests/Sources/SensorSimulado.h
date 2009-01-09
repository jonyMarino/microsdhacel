#ifndef _SENSOR_SIM_H
#define _SENSOR_SIM_H

#include "stddef.h"	
#include "Mydefines.h"
#include "Errores.h"
#include "ClassADC.h"
#include "ClassSensor.h" // Para herencia de clase pura
#include "sensores.h"
#include "MethodContainer.h"
//#include "Capturador.h"
#include "MethodTimer.h"
#include "adjuntador_a_hilo.h"

#pragma CONST_SEG DEFAULT

extern const struct SensorDecLimClass SensorSimulado;													 


/********Clase*********************/
struct SensorSimulado{
  struct SensorVisual super;			// clase base
  uint procVal;  											// Valor Leido y procesado del sensor
  bool procesar;
  TSensorState state;
  byte decimales;
  struct MethodTimer timerMuestreo; 
};
/******************************************/

//void  SensorSimulado_Construct(struct SensorSimulado * self,uint decimales,struct AdjuntadorAHilo*adj,uint tiempoDeMuestreo,const char * desc){

/*
** ===================================================================
**     Method      :  SenTPT_getState 
**     Description :  Indica el estado del sensor(UF,OF,OK)
** ===================================================================
*/
TSensorState SensorSimulado_getState(const struct SensorSimulado * self);
void SensorSimulado_setState(const struct SensorSimulado * self,TSensorState state);
/*
** ===================================================================
**     Method      :  SenRPM_getDesc 
**     Returns		 :  Obtiene la descripcion del sensor
** ===================================================================
*/
char *  SensorSimulado_getDesc(void * _self);
/*
** ===================================================================
**     Method      :  SensorSimulado_forzarProcesamiento 
**     Description :  Procesa como si obtuviese un nuevo valor
** ===================================================================
*/
void SensorSimulado_forzarProcesamiento(void* _self);
/*
** ===================================================================
**     Method      :  SensorSimulado_getValue 
**     Description :  Devuelve el último valor procesado
** ===================================================================
*/
int SensorSimulado_getValue(struct SensorSimulado * self);
void SensorSimulado_setValue(struct SensorSimulado * self,int val);
/*
** ===================================================================
**     Method      :  SensorSimulado_getDesc 
**     Returns		 :  Obtiene el nombre del sensor
** ===================================================================
*/
char *  SensorSimulado_getDesc(void * _self);

/*
** ===================================================================
**     Method      :  SENSOR_setDecimales 
**    Description : Setea la cantidad de decimales
** ===================================================================
*/
byte SensorSimulado_setDecimales(struct SensorSimulado * self, int val);

/*
** ===================================================================
**     Method      :  SENSOR_getDecimales 
**    Description :   Obtiene la cantidad de decimales
** ===================================================================
*/
int SensorSimulado_getDecimales(const struct SensorSimulado * self);
/*
** ==========================================================================
**     Method      :  get_LimInf_Decimales 
**    Type:   Static
**    Description :   Obtiene el minimo valor de decimales que puede setearse
** ==========================================================================
*/
int SensorSimulado_getLimInfDecimales(void);

/*
** ==========================================================================
**     Method      :  get_LimSup_Decimales 
**    Description :   Obtiene el maximo valor de decimales que puede setearse
** ==========================================================================
*/
int SensorSimulado_getLimSupDecimales(const struct SensorSimulado * self);

void SensorSimulado_printVal(struct SensorSimulado * self,struct OutputStream* os);


#endif




