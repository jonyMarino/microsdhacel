#ifndef _SENSORES_H
#define _SENSORES_H 

#include "PE_Types.h"
#include "Sensor.h"

#define _APARATO_VIEJO

enum TADState {
  AD_OK,
  AD_OF,
  AD_UF
};

typedef struct{
  const int * xdat;
  const int * ydat;
  byte max_array;
  byte decimales_max;
  #ifdef _APARATO_VIEJO
  byte decimales_mostrar;
  #endif
}T_Sensor;

#ifdef pirani
  #define SEN_PIR 1
#else
  #define SEN_PIR 0
#endif

#ifdef _APARATO_VIEJO 
  #define NUM_SENSORES 14+SEN_PIR
#else
  #define NUM_SENSORES 9+SEN_PIR
#endif

///////////Sensor//////////////////
#ifdef _APARATO_VIEJO
 typedef enum{
    SENSOR_JB,
    SENSOR_JA,
    SENSOR_N,
    SENSOR_KA,
    SENSOR_KB,
    SENSOR_S,   
   SENSOR_R,
   SENSOR_T,
   SENSOR_PT,  
   #ifdef pirani
   SENSOR_PIR, 
   #endif
   SENSOR_LIN1,
   SENSOR_LIN2,
   SENSOR_LIN3,
   SENSOR_LIN4,
   SENSOR_MV
 }t_sensor;
#else
 typedef enum{
   SENSOR_J,
   SENSOR_N,
   SENSOR_K,
   SENSOR_S,
   SENSOR_R,
   SENSOR_T,
   SENSOR_PT,  
   #ifdef pirani
   SENSOR_PIR, 
   #endif
   SENSOR_LIN,
   SENSOR_MV
 }t_sensor;
#endif

extern const T_Sensor sensorConf[NUM_SENSORES];

/* Devuelve la cantidad de decimales con que se utiliza la tabla del sensor*/
#define SENSOR_Decimales(sensor) sensorConf[sensor].decimales_max		
/* Devuelve la cantidad de decimales con que se muestran las lecturas del sensor*/
#ifdef _APARATO_VIEJO
#define SENSOR_Decimales_Mostrar(sensor) sensorConf[sensor].decimales_mostrar		
#endif
/* Devulve el minimo valor de temperatura admisible(por el aparato) para Sensor*/
#define SENSOR_Minimo(sensor)  sensorConf[sensor].ydat[0]			
/* Devulve el maximo valor de temperatura admisible(por el aparato) para Sensor*/
#define SENSOR_Maximo(sensor)  sensorConf[sensor].ydat[sensorConf[sensor].max_array]			

TADState Linealizar(int Vx, t_sensor sensor, int * Vy);

/*
** ===================================================================
**     Method      : Sens_getColdComp 
**     Parameters  : Vx, sensor
**     Description : Devuelve los centiV de compensación
** ===================================================================
*/
TADState Sens_getColdComp(int temp_amb,int * ColdComp, t_sensor sensor);


bool SENSOR_is_Lineal(t_sensor sensor);

/*
** ===================================================================
**     Function      :  SENSOR_getText 
**     Description :  Devuelve un string con el nombre del sensor
** ===================================================================
*/
const char * SENSOR_getText(byte sensor);

#define MAXAD      10000          //cuentas maximo que salen del ad
#define MAXMV      5000          //decivoltios para esa cuenta
#define MINAD      -2000          //cuentas minimo que salen del ad
#define MINMV      -1000          //decivoltios para esa cuenta

#endif