#ifndef _CONTROL_PID_H
#define _CONTROL_PID_H

#include "PE_Types.h"

#include "Salida.h"
#include "Sensor.h"
#include "MethodTimer.h"
#include "MethodContainer.hpp"
#include "FshTypeSizes.h"

#include "Control.h"

#pragma DATA_SEG PID_DATA                                            
#pragma CODE_SEG PID_CODE
#pragma CONST_SEG DEFAULT 

#define MIN_POTENCIA  0
#define MAX_POTENCIA  1000

#define MAX_VALUE_TIPO_CONTROL 1

typedef enum{
 _CAL, 
 _REF, 
 _MAN 
}T_SalidaControl;

#define MAX_VALUE_SALIDA_CONTROL 2

typedef struct{
  int iSP;
  int iLimInfSP;
  int iLimSupSP;
  int iReset;
  int iHisteresis;
  fbyte eTipoControl;
  fbyte eSalidaControl;
  int iIntegral;
  int iDerivada;
  int iPotenciaInf;
  int iPotenciaSup;
  int iPotenciaManual;
}ControlConf;

#define ControlDefaultConf {			\
  10,															\
  0,															\
  1700,														\
  0,															\
  0,														\
  CNTR_ONOFF,											\
	_CAL,														\
	0,															\
	0,															\
	0,															\
	1000,														\
	0 															\
}																	\

struct ControlPID{
  struct Control _base;
  ControlConf * _conf;
  struct SensorDecLim * sensor;
  struct ISalida * salida;
  T_TipoControl TipoControl;
  int ValControl;
  T_SalidaControl intModSalida;
  int val_ant;
  long buffer_deriv;
  long suminteg;
  struct Method metodoOnNuevaMedicion;
//  struct MethodTimer * timerDesconexion;
  MethodContainer * OnTipoSalidaChange;
};

extern const struct TControlClass ControlPID;

/*
** ===================================================================
**     Method      :  PID_AddOnTSalChange 
**     Description :  Agrega evento de cambio del Tipo de salida
** ===================================================================
*/
void PID_AddOnTSalChange(void * _self,void(*method)(void*,void*),void * Obj);
/*
** ===================================================================
**     Method      :  PID_Disconect 
**     Description :  Desactiva la salida del PID
** ===================================================================
*/
void PID_Disconect(void * self);

/*
** ===================================================================
**     Method      :  PID_Conect 
**     Description :  Activa la salida del PID
** ===================================================================
*/												
void PID_Conect(void * self);  
/*
** ===================================================================
**     Method      :  PID_isConnected 
**     Description :  Activa la salida del PID
** ===================================================================
*/
bool PID_isConnected(void * self);

/*
** ===================================================================
**     Method      :  PID_es_pid 
**     Description :  Determina si se esta como PID o on-off
** ===================================================================
*/
bool PID_es_pid(void * self);

/*
** ===================================================================
**     Method      :  PID_setDutyControl 
**     Description :  Setea el duty de salida
** ===================================================================
*/
void PID_setDutyControl(void * self);
/*
** ===================================================================
**     Method      :  PID_getDuty 
**     Description :  Obtiene el duty de salida
** ===================================================================
*/
int PID_getDuty(void * self);
/*
** ===================================================================
**     Method      :  PID_getSal 
**     Description :  Obtiene un puntero a la salida
** ===================================================================
*/
struct ISalida* PID_getSal(void * self);
/*
** ===================================================================
**     Method      :  PID_getSensor 
**     Description :  Obtiene el sensor utilizado por el control
** ===================================================================
*/
struct Sensor *PID_getSensor(void * self);
/*
** ===================================================================
**     Method      :  PID_setTipoControl 
**     Description :  Funcion para setear el tipo de salida en on-off (salida independiente del periodo)
** ===================================================================
*/

T_TipoControl PID_getTipoControl(void * self);

void PID_setTipoControl(void * self,T_TipoControl TipControl);

/*
** ===================================================================
**     Method      :  PID_getModSal 
**     Description :  MAN - REF -CAL
** ===================================================================
*/
T_SalidaControl PID_getModSal(void * self);

/*
** ===================================================================
**     Method      :  PID_getModSal 
**     Description :  MAN - REF -CAL
** ===================================================================
*/
void PID_setModSal(void * self,T_SalidaControl val);

/*
** ===================================================================
**     Method      :  PID_getValControl 
**     Description :  Obtiene el valor de control (In+Dr+Pr)
** ===================================================================
*/
int PID_getValControl(void * self);
/*
** ===================================================================
**     Method      :  PID_getDec 
**     Description :  Obtiene los decimales del sensor usado
** ===================================================================
*/
uchar PID_getDec(void * self);
/*
** ===================================================================
**     Method      :  PID_getConfSP 
**     Description :  Set Point Configuracion
** ===================================================================
*/
int PID_getLimInfSP(void * self);

int PID_getLimSupSP(void * self);


int PID_getConfSP(void * self);


byte PID_setConfSP(void * self,int val);
/*
** ===================================================================
**     Method      :  PID_getOP_SP 
**     Description :  Obtiene el valor del set point que se utiliza 
**     para las  OPeraciones de calculo del control
** ===================================================================
*/
int PID_getOP_SP(struct ControlPID * _cont);

/*
** ===================================================================
**     Method      :  set_LimInf_SP 
**     Description :  Lim Inf y Sup del SP
** ===================================================================
*/
byte set_LimInf_SP(void * self,int val);

byte set_LimSup_SP(void * self,int val);
int getLimInfSensorControl(void * self);

int getLimSupSensorControl(void * self);

int get_LimInf_LimSupSP(void * self);

int get_LimSup_LimSupSP(void * self);
/*
** ===================================================================
**     Method      :  get_Reset 
**     Description :  
** ===================================================================
*/

int get_Reset(void * self);

byte set_Reset(void * self,int val);

/*
** ===================================================================
**     Method      :  get_TipoControl 
**     Description :  Tipo de control
** ===================================================================
*/
int  get_TipoControl(void * self);

byte set_TipoControl(void * self,int tc);
int get_LimSup_TipoControl(void*);

/*
** ===================================================================
**     Method      :  get_SalControl 
**     Description :  Tipo de salida de Control
** ===================================================================
*/
int get_SalControl(void * self);

byte set_SalControl(void * self,int val);

int get_LimSup_SalControl(void * self);

/*
** ===================================================================
**     Method      :  get_H_Control 
**     Description :  Histeresis
** ===================================================================
*/
int get_H_Control(void * self);
byte set_H_Control(void * self,int val);

/*
** ===================================================================
**     Method      :  get_integral 
**     Description :  Constante de integracion
** ===================================================================
*/
int get_integral(void * self);

byte set_integral(void * self,int val);

int get_LimSup_integral(void*);

/*
** ===================================================================
**     Method      :  get_derivada 
**     Description :  Constante de derivacion
** ===================================================================
*/
int get_derivada(void * self);

byte set_derivada(void * self,int val);

int get_LimSup_derivada(void*);
/*
** ===================================================================
**     Method      :  get_PotenciaInf 
**     Description :  Limite Inferior de Potencia de Salida
** ===================================================================
*/
int get_PotenciaInf(void * self);

byte set_PotenciaInf(void * self,int val);

int get_LimInf_PotenciaInf(void*);
int get_LimSup_PotenciaInf(void * self);

/*
** ===================================================================
**     Method      :  get_PotenciaSup 
**     Description :  Limite Superior de Potencia de Salida
** ===================================================================
*/
int get_PotenciaSup(void * self);
byte set_PotenciaSup(void * self,int val);

int get_LimInf_PotenciaSup(void * self);
int get_LimSup_PotenciaSup(void*);
/*
** ===================================================================
**     Method      :  get_PotenciaManual 
**     Description :  Valor de la Potencia de Salida en Manual
** ===================================================================
*/
int get_PotenciaManual(void * self);
byte set_PotenciaManual(void * self,int val);
int get_LimInf_PotenciaManual(void * self);
int get_LimSup_PotenciaManual(void * self);
 
#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT


#endif

