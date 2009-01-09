/*IMPLEMENTATION MODULE SensorRPM; */
/*
**     Filename  : SensorRPM.C
**     Project   : Controlador
**     Processor : MC9S12GC32CFU
**     Version   : 0.0.1
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 31/03/2008, 14:19
**     Abstract  :
**							Sensor de rpms
*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "limits.h"
#include "IFsh10.h"
#include "PTSL.h"
#include "Math.h"
#include "Errores.h"
#include "Sensor.h"
#include "display.h"
#include "WDog1.h"
#include "SensorSimulado.h"
#include "funciones.h"
#include "display.h"
#include "OutputStream.h"
#include "str_lib.h"

#pragma CONST_SEG DEFAULT


/*  Funciones internas  */
void  SensorSimulado_DefConstruct(struct SensorSimulado * self,va_list * args); 
int SensorSimulado_getValue(struct SensorSimulado * self); 
void SensorSimulado_Print(struct SensorSimulado * self,uchar num_display); 
int SensorSimulado_AdaptVal(struct SensorSimulado * self,int Value);	 
int SensorSimulado_getDecimales(const struct SensorSimulado * self);
void SensorSimulado_procesarCaptura(void * _self);
void SensorSimulado_procesar(void* _self);
int SensorSimulado_getLimSup(void* self){
  return 9999;
}
int SensorSimulado_getLimInf(void* self){
  return -1999;
}
uint SensorSimulado_getTiempoMuestreo(void* _self);
/************************/

const struct SensorDecLimClass SensorSimulado={ 
  &SensorDecLimClass,
  "SensorSimulado",
  &Sensor,
  sizeof(struct SensorSimulado),	//size
  SensorSimulado_DefConstruct,   // constructor
  NULL,                     // destructor
  NULL, // differ
  NULL, // puto
  SensorSimulado_getValue,       // get_Val
  SensorSimulado_Print,
  SensorSimulado_getDesc,
  SensorSimulado_getState,     // Estado
  SensorSimulado_getDecimales,	// Decimales
  SensorSimulado_AdaptVal,     // Adapta un valor cualquiera
  SensorSimulado_getLimSup,		// Limite Superior en formato Print
  SensorSimulado_getLimInf,		// Limite inferior en formato print
  SensorSimulado_getTiempoMuestreo 
};

            
/*
** ===================================================================
**     Method      :  Sensor_Construct 
**     Description :  Constructor del Sensor
** ===================================================================
*/

void  SensorSimulado_Construct(struct SensorSimulado * self,uint decimales,struct AdjuntadorAHilo*adj,uint tiempoDeMuestreo,const char * desc){
  Sensor_constructor(self);
  _SensorVisual_setDescription(self,desc);
  newAlloced(&self->timerMuestreo,&MethodTimer,(ulong)tiempoDeMuestreo,SensorSimulado_procesarCaptura,self);
  if(adj)
    AdjuntadorAHilo_adjuntar(adj,SensorSimulado_procesar,self);
  self->state=SENSOR_OK;
  self->decimales=decimales;
  self->procVal=0;
  self->procesar=FALSE;
}



/*
** ===================================================================
**     Method      :  Sensor_DefConstruct 
**     Description :  Constructor por defecto del Sensor
** ===================================================================
*/

void  SensorSimulado_DefConstruct(struct SensorSimulado * self,va_list * args){
  SensorSimulado_Construct(self,va_arg(*args,uint),va_arg(*args,void*),va_arg(*args,uint),va_arg(*args,char*));  
}

/*
** ===================================================================
**     Method      :  SensorHandler 
**     Description :  Checkea si hay un nuevo valor del AD, 
**                    y si lo hay lo procesa.
** ===================================================================
*/

void SensorSimulado_procesarCaptura(void * _self){
  struct SensorSimulado *_s=_self;
  
  _s->procesar=TRUE;
}

/*
** ===================================================================
**     Method      :  SensorHandler 
**     Description :  Checkea si hay un nuevo valor del AD, 
**                    y si lo hay lo procesa.
** ===================================================================
*/
void SensorSimulado_procesar(void* _self){
  struct SensorSimulado *_s=_self;

  Cpu_DisableInt();  
  if(_s->procesar==TRUE){
    
    _s->procesar=FALSE;
    Sensor_notificarListeners(_self);

  }
  Cpu_EnableInt();
}

/*
** ===================================================================
**     Method      :  SensorSimulado_forzarProcesamiento 
**     Description :  Procesa como si obtuviese un nuevo valor
** ===================================================================
*/
void SensorSimulado_forzarProcesamiento(void* _self){
  struct SensorSimulado *_s=_self;
    //Eventos
    Sensor_notificarListeners(_self);
}


/*
** ===================================================================
**     Method      :  SensorSimulado_getValue 
**     Description :  Devuelve el último valor procesado
** ===================================================================
*/
int SensorSimulado_getValue(struct SensorSimulado * self){
  return self->procVal;
}
/*
** ===================================================================
**     Method      :  SensorSimulado_setValue 
**     Description :  setea el valor
** ===================================================================
*/
void SensorSimulado_setValue(struct SensorSimulado * self,int val){
  self->procVal=val;
}
/*
** ===================================================================
**     Method      :  SensorSimulado_getState 
**     Description :  Indica el estado del sensor(UF,OF,OK)
** ===================================================================
*/
TSensorState SensorSimulado_getState(const struct SensorSimulado * self){
  return self->state;
}
/*
** ===================================================================
**     Method      :  SensorSimulado_getState 
**     Description :  Indica el estado del sensor(UF,OF,OK)
** ===================================================================
*/
void SensorSimulado_setState(struct SensorSimulado * self,TSensorState state){
  self->state=state;
}
/*
** ===================================================================
**     Method      :  SenRPM_getDesc 
**     Returns		 :  Obtiene la descripcion del sensor
** ===================================================================
*/
char *  SensorSimulado_getDesc(void * _self){  
  return _SensorVisual_getDescription(_self);
}

/*
** ===================================================================
**     Method      :  SensorSimulado_Print 
**     Description :  Imprime el valor del sensor
** ===================================================================
*/
void SensorSimulado_Print(struct SensorSimulado * self,uchar num_display){
uint Val=self->procVal;  
											 
  
  /*  
  switch (self->state){
    case SENSOR_OK:
        if(Val>MAX_NUM_DISPLAY)
          PasarASCII(" OF ",num_display);
        else
          Pasar_Numero(Val,num_display,self->decimales);//(uchar)_getDec(self));
    break;

    case SENSOR_OF:
        PasarASCII(" OF ",num_display);
    break;

    case SENSOR_UF:
        PasarASCII(" UF ",num_display);
    break;
  }
    */
}

/*
** ===================================================================
**     Method      :  SensorSimulado_Print 
**     Description :  Imprime el valor del sensor
** ===================================================================
*/
void SensorSimulado_printVal(struct SensorSimulado * self,struct OutputStream* os){
uint Val=self->procVal;  
											 
  
    
  switch (self->state){
    case SENSOR_OK:
        if(Val>MAX_NUM_DISPLAY)
          write(os," OF ");
        else{
          char str[7];
          FloatToStr(Val,str,6,self->decimales);
          write(os,str);
        }
    break;

    case SENSOR_OF:
        write(os," OF ");
    break;

    case SENSOR_UF:
        write(os," UF ");
    break;
  }
    
}



/*
** ===================================================================
**     Method      :  SensorSimulado_AdaptVal 
**     Description :  Adapta el valor que viene con los mismos 
**      decimales con el que se muestra el sensor y lo devuelve con
**      los decimales que se obtienen al hacer un getVal del sensor. 
** ===================================================================
*/
int SensorSimulado_AdaptVal(struct SensorSimulado * self,int Value){
//byte decimales=self->decimales;

  return Value; //* pow10(3-decimales); 
}

/// FUNCIONES DE SETEO Y OBTENCION DE VARIABLES 
/*  Decimales */
/*
** ===================================================================
**     Method      :  SENSOR_setDecimales 
**    Description : Setea la cantidad de decimales
** ===================================================================
*/
byte SensorSimulado_setDecimales(struct SensorSimulado * self, int val){
  self->decimales=val;
  return 0;    
}

/*
** ===================================================================
**     Method      :  SENSOR_getDecimales 
**    Description :   Obtiene la cantidad de decimales
** ===================================================================
*/
int SensorSimulado_getDecimales(const struct SensorSimulado * self){
  return self->decimales;
}

/*
** ==========================================================================
**     Method      :  get_LimInf_Decimales 
**    Type:   Static
**    Description :   Obtiene el minimo valor de decimales que puede setearse
** ==========================================================================
*/
int SensorSimulado_getLimInfDecimales(void){
  return 0;
}

/*
** ==========================================================================
**     Method      :  get_LimSup_Decimales 
**    Description :   Obtiene el maximo valor de decimales que puede setearse
** ==========================================================================
*/
int SensorSimulado_getLimSupDecimales(const struct SensorSimulado * self){
  return 3;
}
/*
** ===================================================================
**    Method      :   SensorSimulado_getTiempoMedicion 
**    Description :   Obtiene el periodo en que se toman las muestras
** ===================================================================
*/
uint SensorSimulado_getTiempoMuestreo(void* _self){
  struct SensorSimulado *_s=_self;
  return Timer_Sys_getTime(&_s->timerMuestreo);
}


/* END SensorRPM. */
