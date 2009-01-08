#ifndef _ALARMA_DE_SENSOR_H
#define _ALARMA_DE_SENSOR_H

#include "PE_Types.h"
#include "PWM.h"
#include "RlxMTimer.h"
#include "Control.h"
#include "FshTypeSizes.h"
									

#pragma DATA_SEG AlarmaDeSensor_DATA                                            
#pragma CODE_SEG AlarmaDeSensor_CODE 
#pragma CONST_SEG DEFAULT   
/*  Tipos enumerativos */
typedef enum{
  AL_EXCESO,
  AL_DEFECTO,
  _eret,
  _dret,
  _dbloq,
  _RET
}TAlarma1;

#define TIPO_ALARMA1_LAST 5

  
typedef enum{
  REL,
  ABS,
  BAN,
}TAlarma2;

#define TIPO_ALARMA2_LAST 2 


/*  Configuracion */
typedef struct{
  int valor;
  int histeresis;
  fbyte tipoControl;
  fbyte tipoAlarma; //(TAlarma1)
  int retLow;  // Valor minimo de retransmision (0%)
  int retHi;   // Valor maximo de retransmision	(100%) 
}TAlarmaConf;


#define ALARMA_DEFAULT_CONF {		\
  0,													  \
  2,														\
  0,											      \
	AL_EXCESO,									  \
	0,														\
  100														\
}																\
 
/*  Definición de la alarma */
struct AlarmaDeSensor{
  struct Control _base;
  TAlarmaConf * _conf;
  struct Sensor * sensor;
  struct PWM * salida;
  byte flagalar;
};

extern const void *const AlarmaDeSensor;

#define VAlarmaDeSensor_RET   vp	 

/*  Methods & Functions*/

/*
** ===================================================================
**     Method      :  AlarmaDeSensor_constructor 
**     Description :  Constructor de la alarma
** ===================================================================
*/
void AlarmaDeSensor_constructor(void * self,void * _conf,void * pid,void * salida,int time_desc);
/*
** ===================================================================
**     Method      :  AlarmaDeSensor_desconectar 
**     Description :  Desconecta la salida de la alarma
** ===================================================================
*/
void AlarmaDeSensor_desconectar(void * self);
/*
** ===================================================================
**     Method      :  AlarmaDeSensor_conectar 
**     Description :  Conecta la salida de la alarma
** ===================================================================
*/
void AlarmaDeSensor_conectar(void * self);
/*
** ===================================================================
**     Method      :  AlarmaDeSensor_manejador 
**     Description :  
** ===================================================================
*/
void AlarmaDeSensor_manejador(void * self, uchar tecla);
/*
** ===================================================================
**     Method      :  AlarmaDeSensor_getHisteresis 
**     Description :  Obtiene histeresis
** ===================================================================
*/
int AlarmaDeSensor_getHisteresis(void * self);
byte AlarmaDeSensor_setHisteresis(void * self,int val);
/*
** ===================================================================
**     Method      :  AlarmaDeSensor_getValor 
**     Description :  Obtiene el valor de alarma
** ===================================================================
*/
int AlarmaDeSensor_getValor(void * self);
byte AlarmaDeSensor_setValor(void * self,int);
int AlarmaDeSensor_limInf(void * self);
int AlarmaDeSensor_limSup(void * self);
uchar AlarmaDeSensor_decimales(void * self);
/*
** ===================================================================
**     Method      :  AlarmaDeSensor_getTipoAlarma 
**     Description :  Obtiene el tipo de alarma	 1
** ===================================================================
*/
int AlarmaDeSensor_getTipoAlarma(void * self);
byte AlarmaDeSensor_setTipoAlarma(void * self,int);
int AlarmaDeSensor_tipoAlarmaLimSup(void * self);
char * AlarmaDeSensor_tipoAlarmaMsj(uchar num_str);

/*
** ===================================================================
**     Method      :  AlarmaDeSensor_getRetLow 
**     Description :  Obtiene el valor 0 de retransmision
** ===================================================================
*/
int AlarmaDeSensor_getRetLow(void*);
byte AlarmaDeSensor_setRetLow(void *,int val);
int AlarmaDeSensor_retLowLimSup(void*);
/*
** ===================================================================
**     Method      :  AlarmaDeSensor_getRetHi 
**     Description :  Obtiene el valor 100 de retransmision
** ===================================================================
*/
int AlarmaDeSensor_getRetHi(void*);
byte AlarmaDeSensor_setRetHi(void *,int val);
int AlarmaDeSensor_retHiLimInf(void*);

 
#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 


#endif