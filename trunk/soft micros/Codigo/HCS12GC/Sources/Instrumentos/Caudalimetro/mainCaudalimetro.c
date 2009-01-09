
/* TestControl.c*/
#include <stddef.h>

#include "Timer.h"
#include "display.h"
#include "WDog1.h"
#include "teclas.h"
#include "Object.h"
#include "ClassADC.h"
#include "Grabacion.h"
#include "PWM.h"
#include "DiagramaNavegacion.h"
#include "PWM_Hmi.h"
#include "SnsHmi.h"
#include "BoxProp.h"
#include "Sets.h"
#include "Sensores.h"
#include "SensorTPT_Class.h"
#include "ControlPID.h"
#include "PidHmi.h"
#include "PropNumPV.h"
#include "MessagesOut.h"
#include "ModBusHmi.h"
#include "com_events.h"
#include "Pid2SPHmi.h"
#include "ControlPID2SP.h"
#include "InpSP2.h"
#include "BoxPrincipalNC.h"
#include "FlashBkpEnFlash.h"
#include "Termometro.h"
#include "timer_interrupt.h"
#include "FstBoxPointer.h"
#include "BoxList.h"
#include "Access.h"
#include "AlarmaControl.h"
#include "RlxMTimer.h"
#include "LedsSalida.h"
#include "ThreadAdjuntable.h"
#include "Thread.h"
#include "Integrador.h"

/* Definiciones */

/*  Tiempo inicial en el que el control permanece desconectado  */
#ifdef _COLADA_CALIENTE  
  #define SALIDA_TIEMPO_DESCONECTADA 20000 
#else
  #define SALIDA_TIEMPO_DESCONECTADA 3000   //tiene que alcanzar para hacer 2 mediciones
#endif

/* Prototipos */
void SD100_conectarSalidas(void * self);

/* Variables */
struct Termometro termometro;
struct Integrador integrador;

static const struct getter * gettersAMostrar[]={
  &termometro.sensor[0],
  &integrador
};					

static const NEW_ARRAY_LIST(variablesPantallaPrincipal,gettersAMostrar);

const struct BlockConstBoxPriNC CBox_Pri={
      &BoxPriNC,							/* funcion que procesa al box*/
      &variablesPantallaPrincipal,      
      NULL					
};

/*  COMUNICACION  */
  /*PWM*/
//  static const NEW_NODO_IC_MODBUS(PWM1Com,&PWM_GETTERS_ARRAY,1000,&pwmConEventoPeriodo[0]);
  /*Sensor*/
  static const NEW_NODO_IC_MODBUS(Sen1Com,&SNS_GETTERS_ARRAY,1100,&termometro.sensor[0]);
  /*Alarma*/
//  static const NEW_NODO_IC_MODBUS(Al1Com,&AL_GETTERS_ARRAY,1200,&alarma[0]);
  /*Comunicacion*/
  static const NEW_NODO_IC_MODBUS(ModBusCom,&MODBUS_GETTERS_ARRAY,1400,NULL);
  /*Codigo*/
  static const NEW_NODO_IC_MODBUS(CodCom,&COD_GETTERS_ARRAY,1500,NULL);


  static const struct NodoICModBus *const  nodosComunicacion[]={
     //Pwm
//     &PWM1Com,
     //Sensor
     &Sen1Com,
//     &Sen2Com,    
     //Alarma
//     &Al1Com,

     //Pid
//     &Pid1Com,
             
     //Comunicacion
     &ModBusCom,    
     //codigo
     &CodCom
  };
  static const NEW_ARRAY_LIST(arrayNodosComunicacion,nodosComunicacion);
/*  FIN COMUNICACION  */

/*  Diagrama de navegacion  */
//Operador
  //Principal
static const NEW_FST_BOX_POINTER(Principal,&CBox_Pri,NULL,0);
  //Control
//static const NEW_FST_BOX_POINTER(Cntrl1OP1,&PID_HMI_FST_OP_BOX,&control[0],1);
  //Alarma
//static const NEW_FST_BOX_POINTER(AL1OP,&ALARMA_DE_SENSOR_HMI_FST_OP,&alarma[0],1);
  

static const struct FstBoxPointer *const OpArray[]={
  &Principal
//  &Cntrl1OP1,

//  &Cntrl1OP2,    
//  &AL1OP,  

};


static const NEW_BOX_LIST(OpList,OpArray,"op");

//CAL
static const NEW_FST_BOX_POINTER(Sensor1List,&SNS_HMI_FST_BOX,&termometro.sensor[0],1);
//static const NEW_FST_BOX_POINTER(Sensor2List,&SNS_HMI_FST_BOX,&termometro.sensor[1],2);

static const struct FstBoxPointer *const CalArray[]={
  &Sensor1List 
//  &Sensor2List,    
};

static const NEW_BOX_LIST(Cal,CalArray,"CAL");


//SET
  //Comunicacion
static const NEW_FST_BOX_POINTER(ModBusSet,&MOD_BUS_HMI_FST_BOX_SET,0,0);
  //SetC
static const NEW_FST_BOX_POINTER(SetsSet,&SETS_FST_BOX_SET,0,0);
  

static const struct FstBoxPointer *const SetArray[]={
  &ModBusSet,
  &SetsSet  
};

static const NEW_BOX_LIST(Set,SetArray,"SEt");


// Acceso comun
static const struct BoxList *const BoxListArray[]={
  &Cal,
  &Set
};

static const NEW_ACCESS(accesoComun,BoxListArray,"Cod",CONTENEDOR_CODIGO);

static const struct Access *const AccessArray[]={
  &accesoComun
};

static const NEW_ARRAY_LIST(AccessList,AccessArray);


/****************/


NEW_FLASH_BKP_EN_FLASH(flash,0x4200);
struct ManejadorMemoria *const pFlash= &flash;

void Caudalimetro_procesar(uchar tecla){ 
  DN_Proc(tecla);
  if(tecla == 's')
    Integrador_resetAcumulador(&integrador);
}


void main(void){
  
  char tecla;    

  newAlloced(&termometro,&Termometro,&flash);
  newAlloced(&integrador,&Integrador,_getSensor( &termometro , 0) );
  Integrador_setLimiteSuperior(&integrador,MAX_NUM_DISPLAY);
  Integrador_setLimiteInferior(&integrador,MIN_NUM_DISPLAY);
  Integrador_setConstanteIntegracion(&integrador,3600);
  
  com_initialization(&arrayNodosComunicacion);
   
  //Diagrama de navegacion
  DN_staticInit(&OpList,&AccessList);

														 
  for(;;){
    tecla=get_key();  
    //Eventos
        
    Caudalimetro_procesar(tecla);
    Termometro_mainLoop(&termometro);  
  }
}



