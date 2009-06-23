/* TestControl.c*/
#include "stddef.h"
#include "stdtypes.h"
#include "Timer.h"
#include "display.h"
#include "WDog1.h"
#include "teclas.h"
#include "Object.h"
#include "ClassADC.h"
#include "Grabacion.h"
#include "DiagramaNavegacion.h"
#include "SnsHmi.h"
#include "BoxProp.h"
#include "Sets.h"
#include "Sensores.h"
#include "SensorTPT_Class.h"
#include "RlxMTimer.h"
#include "Adquisidor.h"
#include "AdquisidorHmi.h"
#include "com_events.h"
#include "Terminal.h"
#include "termio.h"
#include "hidef.h"
#include "stdio.h"
#include "FlashBkp256.h"
#include "Termometro.h"
#include "timer_interrupt.h"
#include "ModBusHmi.h"
#include "BoxPriAdquisidor.h"
#include "AdquisidorSimple.h"
#include "System.h"
#include "dateTimeVista.h"
#include "ArrayList.h"
#include "FstBoxPointer.h"
#include "BoxList.h"
#include "Access.h"
#include "AdquisidorHmi.h"

#define CNTR_TIME_DISCONECT 2000


NEW_FLASH_BKP_256(flash,0x4200);
const struct ManejadorMemoria * pFlash = &flash;

struct AdquisidorSimple adquisidorSimple;


const struct BlockConstBoxPri CBox_Pri={
      &BoxPriAdquisidor,							/* funcion que procesa al box*/
      adquisidorSimple.termometro.sensor,
      &adquisidorSimple.mensajes						
};

/*  COMUNICACION  */
  /*Adquisidor*/
  static const NEW_NODO_IC_MODBUS(DateTime1Com,&DATE_TIME_GETTERS_ARRAY,1000,&baseTiempo);
  static const NEW_NODO_IC_MODBUS(Adq1Com,&ADQ_GETTERS_ARRAY,1054,_getAdquisidor(&adquisidorSimple));  
  /*Sensor*/
  static const NEW_NODO_IC_MODBUS(Sen1Com,&SNS_GETTERS_ARRAY,1100,_getSensor(&adquisidorSimple,0));
  /*Comunicacion*/
  static const NEW_NODO_IC_MODBUS(ModBusCom,&MODBUS_GETTERS_ARRAY,1400,NULL);
  /*Codigo*/
  static const NEW_NODO_IC_MODBUS(CodCom,&COD_GETTERS_ARRAY,1500,NULL);
    
    

  static const struct NodoICModBus *const  nodosComunicacion[]={
     //Base de tiempo
     &DateTime1Com,
     //Adquisidor
     &Adq1Com,
     //Sensor
     &Sen1Com,    
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

//static const NEW_FST_BOX_POINTER(fecha,&CBox_Fecha,NULL,0); 


static const struct FstBoxPointer *const OpArray[]={
  &Principal,
  //&fecha
};


static const NEW_BOX_LIST(OpList,OpArray,"op");


//ADQ

static const NEW_FST_BOX_POINTER(AdqList,&ADQ_FST_BOX,_getAdquisidor(&adquisidorSimple),0);

static const struct FstBoxPointer *const AdqArray[]={
  &AdqList   
};
static const NEW_BOX_LIST(Adq,AdqArray,"Adq");

//CAL
static const NEW_FST_BOX_POINTER(Sensor1List,&SNS_HMI_FST_BOX,_getSensor(&adquisidorSimple,0),0);

static const struct FstBoxPointer *const CalArray[]={
  &Sensor1List   
};

static const NEW_BOX_LIST(Cal,CalArray,"CAL");


//SET
static const NEW_FST_BOX_POINTER(DateList,&DATE_TIME_BOX,&baseTiempo,0);

  //Comunicacion
static const NEW_FST_BOX_POINTER(ModBusSet,&MOD_BUS_HMI_FST_BOX_SET,0,0);
  
  //SetC
static const NEW_FST_BOX_POINTER(SetsSet,&SETS_FST_BOX_SET,0,0);
  

static const struct FstBoxPointer *const SetArray[]={
  &DateList,
  &ModBusSet,
  &SetsSet  
};

static const NEW_BOX_LIST(Set,SetArray,"SEt");



// Acceso comun
static const struct BoxList *const BoxListArray[]={
  &Adq,
  &Cal,
  &Set
};

static const NEW_ACCESS(accesoComun,BoxListArray,"Cod",CONTENEDOR_CODIGO);

static const struct Access *const AccessArray[]={
  &accesoComun
};

static const NEW_ARRAY_LIST(AccessList,AccessArray);




void main (void){

  char tecla;
  
  System_init();
  newAlloced(&adquisidorSimple,&AdquisidorSimple,NULL,&flash);
   															 //012345678901234567890123456789012345678
  
 
  com_initialization(&arrayNodosComunicacion);
      
  
  DN_staticInit(&OpList,&AccessList);
  
  
  
  for(;;){
		
		
    tecla=get_key();  
    //Eventos
    DN_Proc(tecla);
    
    mainLoop(&adquisidorSimple);
    
  }
}