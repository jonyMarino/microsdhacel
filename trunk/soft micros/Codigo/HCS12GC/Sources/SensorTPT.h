#ifndef _SENSOR_TPT_CLASS_H
#define _SENSOR_TPT_CLASS_H

#include "stddef.h"	
#include "Mydefines.h"
#include "Errores.h"
#include "ClassADC.h"
#include "ClassSensor.h" // Para herencia de clase pura

extern const struct TableSenTPT * TSensor_TermoPT;



/********Objeto*********************/
typedef enum {
  SENSOR_OK,  //OK
  SENSOR_OF,  //Over Flow
  SENSOR_UF   //Under Flow
}TSensorState;

typedef struct {
  t_sensor eSensor;
  byte iDecimales;
  byte iFiltro;
  int iOffset;
  int iGanancia;
  int iCeroTermopar;
  int iGananciaTermopar;
  int iCeroPT100;
  int iGananciaPT100;
}SensorConf;

struct TSensor_TermoPT{
  const struct TSensor * sensor;			// vtable
  volatile const SensorConf * conf;		// Variables de configuración en Rom
  struct TAdc * Adc;  											  // Pin del ADC al que pertenece este sensor
  int ProcVal;  											// Valor Leido y procesado del sensor
  bool newVal;                        //indica si el valor es nuevo
  long buffer_fil;                     // Privado: acumulacion del filtro  
  TSensorState state;									// Estado del sensor
};
/******************************************/




/*  CONFIGURACION */


#endif