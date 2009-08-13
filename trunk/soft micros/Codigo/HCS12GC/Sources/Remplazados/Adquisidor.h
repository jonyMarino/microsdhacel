#ifndef _Adquisidor
#define _Adquisidor

#include "Object.h"
#include "Configuracion.h"
#include "PE_Types.h"
#include "stdtypes.h"
#include "ClassSensor.h"
#include "GettersVisual.h"
#include "TmDt1.h"
#include "Errores.h"
#include "RlxMTimer.h"
#include "FshTypeSizes.h"



typedef enum{
  ADQ_ERASEMEM,
  ADQ_STOPADQ
}TAdqStrategy;

#define _MAX_VALUE_ADQ_STRATEGY 1

struct AdqConf{
  fbyte Adquirir;
  word intervalo;             //en segundos
  fbyte Estrategia; 		 //(TAdqStrategy)
  word * MemAddrStart; 
  word * MemAddrEnd;             
};

#define ADQ_DEFAULT_CONF 					 \
  FALSE,													 \
  5,															 \
  ADQ_STOPADQ,										 \
  (word *)(0x4400),								 \
  (word *)(FLASH_ADQUISIDOR_END) 

typedef enum{
  ADQ_NO,
  ADQ_YES,
  ADQ_HULT,
  ADQ_FULL  
}TAdqState;

struct Adquisidor{
  struct Object super;
//Private:
  struct AdqConf * _conf;
  word * ActualAddr;					          //Direccion actual donde grabar los datos 
  word * OlderPageAddr;
//Protected:
  
  struct GetterVisual ** _getter;
  struct SensorVisual * sensor;
  TAdqState Estado_Adquisicion;
  struct RlxMTimer * Adq_Timer;
  void (*pfMemFullStrategy)(void*,word*);	/* puntero a funcion del metodo que 
                                          ejecuta la estrategia de memoria llena  
                                          */
//Private:
  bool grabando;
};

extern const struct Class Adquisidor;

/*
** ===================================================================
**     Method      :  Adq_Constructor 
**    Description  :  Constructor del Objeto
** ===================================================================
*/
//void * newObj(Adquisidor,struct AdqConf * conf);

/*
** ===================================================================
**     Method      :  Adq_Handler 
**    Type:        :  Private
**    Description  :  Manejador del Adquisidor
** ===================================================================
*/
void Adq_Handler(void * self);

/*
** ===================================================================
**     Method      :  Adq_isTimeSet
**    Description  :  indica si se introdujo el tiempo
** ===================================================================
*/
bool Adq_isTimeSet(void *_self);

/*
** ===================================================================
**     Method      :  Adq_Start
**    Description  :  Empieza la adquisicion (si es que la memoria no
**                    se encuentra en full)
** ===================================================================
*/
void Adq_Start(void *_self);

/*
** ===================================================================
**     Method      :  Adq_Stop 
**    Description  :  Detiene la adquisicion
** ===================================================================
*/
void Adq_Stop(void *_self);
/*
** ===================================================================
**     Method      :  Adq_Escribir_Stop 
**    Description  :  Escribe en la direccion actual, que se detuvo
**                   la adquisicion por orden del usuario
** ===================================================================
*/
void Adq_Escribir_Stop(void* _self);
/*
** ===================================================================
**     Method      :  Adq_SizeOfHeader 
**    Type         :  Private
**    Description  :  Devuelve el tamanio del encabezado
** ===================================================================
*/
word Adq_SizeOfHeader(void * _self);
/*
** ===================================================================
**     Method      :  Adq_SizeOfWriteParams 
**    Type         :  Private
**    Description  :  Devuelve el tamanio de la escritura de parametros
** ===================================================================
*/
word Adq_SizeOfWriteParams(void * _self);
/*
** ===================================================================
**     Method      :  Adq_getActualState
**    Description  :  Obtiene el estado del adquisidor (      "no  ",									
**			"Si  ",
**			"HLt ",
**			"FULL")
** ===================================================================
*/
int  Adq_getActualState(void * _self);
/*
** ===================================================================
**     Method      :  Adq_SetState
**    Description  :  Setea el estado del adquisidor (NO/YES)
** ===================================================================
*/
TError  Adq_SetState(void * _self, int val);
/*
** ===================================================================
**     Method      :  Adq_getState
**    Description  :  Setea el estado del adquisidor (NO/YES)
** ===================================================================
*/
int  Adq_getState(void * _self);
/*
** ===================================================================
**     Method      :  Adq_StateLimSup
**    Description  :  Limite Superior de estado
** ===================================================================
*/
int Adq_StateLimSup(void*_self);
/*
** ===================================================================
**     Method      :  Adq_StateLimInf
**    Description  :  Limite Inferior de estado
** ===================================================================
*/
int Adq_StateLimInf(void*_self);
/*
** ===================================================================
**     Method      :  Adq_getStateStr
**    Description  :  Obtiene el string de state
** ===================================================================
*/
char * Adq_getStateStr(byte num);
/*
** ===================================================================
**     Method      :  Adq_SetStrategy
**    Description  :  Setea la estrategia ante memoria llena
** ===================================================================
*/
TError  Adq_setStrategy(void * _self, int val);
/*
** ===================================================================
**     Method      :  Adq_getState
**    Description  :  Obtiene la estrategia ante memoria llena
** ===================================================================
*/
int  Adq_getStrategy(void * _self);

/*
** ===================================================================
**     Method      :  Adq_LimSupStrategy
**    Description  :  Limite Superios del valor de estrategia
** ===================================================================
*/
int  Adq_LimSupStrategy(void * _self);
/*
** ===================================================================
**     Method      :  Adq_getStrStrategy
**    Description  :  Textos de estrategia
** ===================================================================
*/
char * Adq_getStrStrategy(uchar num);

/*
** ===================================================================
**     Method      :  Adq_setIntervalo
**    Description  :  Setea el intervalo de muestreo
** ===================================================================
*/
TError Adq_setIntervalo(void * _self,int val);

/*
** ===================================================================
**     Method      :  Adq_getIntervalo
**    Description  :  Obtiene el intervalo de muestreo
** ===================================================================
*/
int Adq_getIntervalo(void * _self);
/*
** ===================================================================
**     Method      :  Adq_LimInfIntervalo
**    Description  :  Limite Inferior de Intervalo
** ===================================================================
*/
int Adq_LimInfIntervalo(void * _self);

/*
** ===================================================================
**     Method      :  Adq_BorrarPage
**    Description  :  Estando el _ADQUISIDOR en FULL,
**                    si se borra la pagina siguiente a la que se esta
**                    escribiendo, el estado del _ADQUISIDOR pasara de 
**                    "FULL" a "no  ". 
** ===================================================================
*/
TError Adq_ErasePage(void* _self, word * page);

/*
** ===================================================================
**     Method      :  Adq_ErasePages
**    Description  :  Borra todas las paginas del adquisidor 
** ===================================================================
*/
TError Adq_ErasePages(void* _self, word ok);

/*
** ===================================================================
**     Method      :  Adq_BorrarPagina
**    Description  :  Obtiene la pagina que esta siendo usada y 
**                  no puede borrarse.
** ===================================================================
*/
int Adq_getPaginaActual(void* _self);

/*
** ===================================================================
**     Method      :  Adq_getPaginasStart
**    Description  :  Dirección donde comienzan las paginas
** ===================================================================
*/
int Adq_getPaginasStart(void* _self);

/*
** ===================================================================
**     Method      :  Adq_getPaginasEnd
**    Description  :  Direccion donde terminan las paginas
** ===================================================================
*/
int Adq_getPaginasEnd(void* _self);

#endif