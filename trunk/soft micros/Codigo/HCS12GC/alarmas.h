#ifndef _ALARMAS_H
#define _ALARMAS_H

#include "PE_Types.h"
#include "ControlPID.h"
#include "PWM.h"
#include "RlxMTimer.h"
									

#pragma DATA_SEG ALARMA_CONTROLADOR_DATA                                            
#pragma CODE_SEG ALARMA_CONTROLADOR_CODE 
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
  REFR,
  BAN,
}TAlarma2;

#define TIPO_ALARMA2_LAST 3 



/*  Configuracion */
typedef struct{
  int iAlarma;
  int iHistAlarma;
  uchar tipoControl;
  TAlarma1 eTipoAlarma1;
  TAlarma2 eTipoAlarma2;
  int iRetLow;  // Valor minimo de retransmision (0%)
  int iRetHi;   // Valor maximo de retransmision	(100%) 
}TAlarmaConf;


#define ALARMA_DEFAULT_CONF {		\
  0,													  \
  2,														\
  0,											      \
	REL,												  \
	0,														\
  100														\
}																\
 
/*  Definición de la alarma */
struct AlarmaMult{
  struct Control _base;
  TAlarmaConf * _conf;
  struct ControlPID * pid;
  struct PWM * salida;
  T_TipoControl TipoControl;
  bool isConnected;
  byte flagalar;
  struct RlxMTimer * Alartimer;
};

extern const void *const AlarmaMult;

#define VAL_RET   vp	 

/*  Methods & Functions*/

/*
** ===================================================================
**     Method      :  AL_Constructor 
**     Description :  Constructor de la alarma
** ===================================================================
*/
void AL_Constructor(void * self,void * _conf,void * pid,void * salida,int time_desc);
/*
** ===================================================================
**     Method      :  AL_Disconnect 
**     Description :  Desconecta la salida de la alarma
** ===================================================================
*/
void AL_Disconnect(void * self);
/*
** ===================================================================
**     Method      :  AL_Connect 
**     Description :  Conecta la salida de la alarma
** ===================================================================
*/
void AL_Connect(void * self);
/*
** ===================================================================
**     Method      :  AL_FstConect 
**     Description :  Conecta por primera vez la salida de la alarma
** ===================================================================
*/
void AL_FstConect(void * self);
/*
** ===================================================================
**     Method      :  AL_Handler 
**     Description :  
** ===================================================================
*/
void AL_Handler(void * self, uchar tecla);
/*
** ===================================================================
**     Method      :  AL_es_pid 
**     Description :  
** ===================================================================
*/
bool AL_es_pid(void * self);
/*
** ===================================================================
**     Method      :  AL_getHisteresis 
**     Description :  Obtiene histeresis
** ===================================================================
*/
int AL_getHisteresis(void * self);
byte set_H_Alarma(void * self,int val);
/*
** ===================================================================
**     Method      :  get_AL 
**     Description :  Obtiene el valor de alarma
** ===================================================================
*/
int get_AL(void * self);
byte set_AL(void * self,int);
int get_LimInf_AL(void * self);
int get_LimSup_AL(void * self);
uchar AL_getDec(void * self);
/*
** ===================================================================
**     Method      :  get_TipoAlarma1 
**     Description :  Obtiene el tipo de alarma	 1
** ===================================================================
*/
int get_TipoAlarma1(void * self);
byte set_TipoAlarma1(void * self,int);
int get_LimSup_TipoAlarma1(void * self);
char * AL_getTAL1str(uchar num_str);
/*
** ===================================================================
**     Method      :  get_TipoAlarma1 
**     Description :  Obtiene el tipo de alarma 2
** ===================================================================
*/
int get_TipoAlarma2(void * self);
byte set_TipoAlarma2(void * self,int);
int get_LimSup_TipoAlarma2(void * self);
char * AL_getTAL2str(uchar num_str);
/*
** ===================================================================
**     Method      :  get_RetLow 
**     Description :  Obtiene el valor 0 de retransmision
** ===================================================================
*/
int get_RetLow(void*);
byte set_RetLow(void *,int val);
int get_LimSup_RetLow(void*);
/*
** ===================================================================
**     Method      :  get_RetHi 
**     Description :  Obtiene el valor 100 de retransmision
** ===================================================================
*/
int get_RetHi(void*);
byte set_RetHi(void *,int val);
int get_LimInf_RetHi(void*);

 
#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 


#endif