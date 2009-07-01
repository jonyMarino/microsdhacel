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
#include "PropNumPV.h"
#include "MessagesOut.h"
#include "ModBusHmi.h"
#include "com_events.h"
#include "BoxPrincipalNC.h"
#include "FlashBkpEnFlash.h"
#include "Termometro.h"
#include "timer_interrupt.h"
#include "PWMTimer.h"
#include "PWMHard01.h"
#include "PWMHard23.h"
#include "FstBoxPointer.h"
#include "BoxList.h"
#include "Access.h"
#include "AlarmaDeSensor.h"
#include "RlxMTimer.h"
#include "LedsSalida.h"
#include "ThreadAdjuntable.h"
#include "Thread.h"
#include "AlarmaDeSensorHmi.h"
#include "PWMPeriodoEvent.h"
#include "PWMSoft.h"
#include "Adquisidor.h"
#include "AdquisidorHmi.h"
#include "AdquisidorSimple.h"
#include "dateTimeVista.h"
#include "System.h"
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
struct AdquisidorSimple adquisidorSimple;

#pragma CONST_SEG PARAMETERS_PAGE
volatile const TConfPWM pwm_config[CANTIDAD_SAL_ALARMA+CANTIDAD_SAL_CONTROL];

volatile const TAlarmaConf alar_conf[CANTIDAD_SAL_ALARMA]={
  ALARMA_DEFAULT_CONF,
  #if CANTIDAD_SAL_ALARMA>1 
    ALARMA_DEFAULT_CONF,
      #if CANTIDAD_SAL_ALARMA>2
        ALARMA_DEFAULT_CONF,
        #if CANTIDAD_SAL_ALARMA>3
          ALARMA_DEFAULT_CONF
        #endif
      #endif
  #endif
};

#pragma CONST_SEG DEFAULT


struct PWM * pwm[CANTIDAD_SAL_ALARMA];
struct TAdc  AD1[CANTIDAD_CANALES];
struct AlarmaDeSensor alarma[CANTIDAD_SAL_ALARMA];

struct PWMTimer pwmsTimer[CANTIDAD_SAL_ALARMA];
    
const struct getter * gettersAMostrar[]={
  &termometro.sensor[0],
  &termometro.sensor[1],
  &termometro.sensor[2],
  &termometro.sensor[3]
};					


static struct MessageOut msj[CANTIDAD_SAL_CONTROL];

const struct BlockConstBoxPriNC CBox_Pri={
      &BoxPriNC,							/* funcion que procesa al box*/
      gettersAMostrar,      
      msj						
};

/*  COMUNICACION  */
  /*PWM*/
  static const NEW_NODO_IC_MODBUS(PWM1Com,&PWM_GETTERS_ARRAY,1000,&pwmsTimer[0]);
  static const NEW_NODO_IC_MODBUS(PWM2Com,&PWM_GETTERS_ARRAY,1010,&pwmsTimer[1]);
  static const NEW_NODO_IC_MODBUS(PWM3Com,&PWM_GETTERS_ARRAY,1020,&pwmsTimer[2]);
  static const NEW_NODO_IC_MODBUS(PWM4Com,&PWM_GETTERS_ARRAY,1030,&pwmsTimer[3]);
  /*Sensor*/
  static const NEW_NODO_IC_MODBUS(Sen1Com,&SNS_GETTERS_ARRAY,1100,&termometro.sensor[0]);
  static const NEW_NODO_IC_MODBUS(Sen2Com,&SNS_GETTERS_ARRAY,1120,&termometro.sensor[1]);
  static const NEW_NODO_IC_MODBUS(Sen3Com,&SNS_GETTERS_ARRAY,1140,&termometro.sensor[2]);
  static const NEW_NODO_IC_MODBUS(Sen4Com,&SNS_GETTERS_ARRAY,1160,&termometro.sensor[3]);
  /*Alarma*/
  static const NEW_NODO_IC_MODBUS(Al1Com,&AL_GETTERS_ARRAY,1200,&alarma[0]);
  static const NEW_NODO_IC_MODBUS(Al2Com,&AL_GETTERS_ARRAY,1220,&alarma[1]);
  static const NEW_NODO_IC_MODBUS(Al3Com,&AL_GETTERS_ARRAY,1240,&alarma[2]);
  static const NEW_NODO_IC_MODBUS(Al4Com,&AL_GETTERS_ARRAY,1260,&alarma[3]);
  /*Comunicacion*/
  static const NEW_NODO_IC_MODBUS(ModBusCom,&MODBUS_GETTERS_ARRAY,1400,NULL);
  /*Codigo*/
  static const NEW_NODO_IC_MODBUS(CodCom,&COD_GETTERS_ARRAY,1500,NULL);

  /*Adquisidor*/
  static const NEW_NODO_IC_MODBUS(DateTime1Com,&DATE_TIME_GETTERS_ARRAY,1000,&baseTiempo);
  static const NEW_NODO_IC_MODBUS(Adq1Com,&ADQ_GETTERS_ARRAY,1054,_getAdquisidor(&adquisidorSimple));

  static const struct NodoICModBus *const  nodosComunicacion[]={
     //Pwm
     &PWM1Com,
     &PWM2Com,
     &PWM3Com,
     &PWM4Com,
     //Sensor
     &Sen1Com,
     &Sen2Com,
     &Sen3Com,
     &Sen4Com,     
     //Alarma
     &Al1Com,
     &Al2Com,
     &Al3Com,
     &Al4Com,     
            
     //Comunicacion
     &ModBusCom,
     //Base de tiempo
     &DateTime1Com,
     //Adquisidor
     &Adq1Com,    
     //codigo
     &CodCom
  };
  static const NEW_ARRAY_LIST(arrayNodosComunicacion,nodosComunicacion);
  

/*  FIN COMUNICACION  */

/*  Diagrama de navegacion  */
//Operador
  //Principal
static const NEW_FST_BOX_POINTER(Principal,&CBox_Pri,NULL,0);
//Alarma
static const NEW_FST_BOX_POINTER(AL1OP,&ALARMA_DE_SENSOR_HMI_FST_OP,&alarma[0],1);
static const NEW_FST_BOX_POINTER(AL2OP,&ALARMA_DE_SENSOR_HMI_FST_OP,&alarma[1],2);
static const NEW_FST_BOX_POINTER(AL3OP,&ALARMA_DE_SENSOR_HMI_FST_OP,&alarma[2],3);
static const NEW_FST_BOX_POINTER(AL4OP,&ALARMA_DE_SENSOR_HMI_FST_OP,&alarma[3],4);
  

static const struct FstBoxPointer *const OpArray[]={
  &Principal,
  &AL1OP,  
  &AL2OP, 
  &AL3OP,
  &AL4OP,  
};


static const NEW_BOX_LIST(OpList,OpArray,"op");

//ADQ

static const NEW_FST_BOX_POINTER(AdqList,&ADQ_FST_BOX,_getAdquisidor(&adquisidorSimple),0);

static const struct FstBoxPointer *const AdqArray[]={
  &AdqList   
};
static const NEW_BOX_LIST(Adq,AdqArray,"Adq");


//CAL
static const NEW_FST_BOX_POINTER(Sensor1List,&SNS_HMI_FST_BOX,&termometro.sensor[0],1);
static const NEW_FST_BOX_POINTER(Sensor2List,&SNS_HMI_FST_BOX,&termometro.sensor[1],2);
static const NEW_FST_BOX_POINTER(Sensor3List,&SNS_HMI_FST_BOX,&termometro.sensor[2],3);
static const NEW_FST_BOX_POINTER(Sensor4List,&SNS_HMI_FST_BOX,&termometro.sensor[3],4);

static const struct FstBoxPointer *const CalArray[]={
  &Sensor1List, 
  &Sensor2List, 
  &Sensor3List, 
  &Sensor4List    
};

static const NEW_BOX_LIST(Cal,CalArray,"CAL");

//TUN
static const NEW_FST_BOX_POINTER(PWM1Tun,&PWM_AL_VISTA_FST_TUN_BOX,&pwmsTimer[0],1);
static const NEW_FST_BOX_POINTER(PWM2Tun,&PWM_AL_VISTA_FST_TUN_BOX,&pwmsTimer[1],2); 
static const NEW_FST_BOX_POINTER(PWM3Tun,&PWM_AL_VISTA_FST_TUN_BOX,&pwmsTimer[2],3);
static const NEW_FST_BOX_POINTER(PWM4Tun,&PWM_AL_VISTA_FST_TUN_BOX,&pwmsTimer[3],4);


  //Alarma
static const NEW_FST_BOX_POINTER(AL1TUN,&ALARMA_DE_SENSOR_HMI_FST_TUN,&alarma[0],1);
static const NEW_FST_BOX_POINTER(AL2TUN,&ALARMA_DE_SENSOR_HMI_FST_TUN,&alarma[1],2);
static const NEW_FST_BOX_POINTER(AL3TUN,&ALARMA_DE_SENSOR_HMI_FST_TUN,&alarma[2],3);
static const NEW_FST_BOX_POINTER(AL4TUN,&ALARMA_DE_SENSOR_HMI_FST_TUN,&alarma[3],4);
  
static const struct FstBoxPointer *const TunArray[]={
  &PWM1Tun, 
  &PWM2Tun,
  &PWM3Tun, 
  &PWM4Tun,
  &AL1TUN,
  &AL2TUN,
  &AL3TUN,
  &AL4TUN    
};

static const NEW_BOX_LIST(Tun,TunArray,"tun");

//SET
  //Control

  //Alarma
static const NEW_FST_BOX_POINTER(AL1SET,&ALARMA_DE_SENSOR_HMI_FST_SET,&alarma[0],1);
static const NEW_FST_BOX_POINTER(AL2SET,&ALARMA_DE_SENSOR_HMI_FST_SET,&alarma[1],2);
static const NEW_FST_BOX_POINTER(AL3SET,&ALARMA_DE_SENSOR_HMI_FST_SET,&alarma[2],3);
static const NEW_FST_BOX_POINTER(AL4SET,&ALARMA_DE_SENSOR_HMI_FST_SET,&alarma[3],4);

  //Comunicacion
static const NEW_FST_BOX_POINTER(ModBusSet,&MOD_BUS_HMI_FST_BOX_SET,0,0);
  //SetC
static const NEW_FST_BOX_POINTER(SetsSet,&SETS_FST_BOX_SET,0,0);
  

static const struct FstBoxPointer *const SetArray[]={
  &AL1SET,
  &AL2SET,
  &AL3SET,
  &AL4SET,
  &ModBusSet,
  &SetsSet  
};

static const NEW_BOX_LIST(Set,SetArray,"SEt");




// Acceso comun
static const struct BoxList *const BoxListArray[]={
  &Adq,
  &Tun,
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



struct RlxMTimer timerConexionSalidas;


const LedConfig configuracionLedsSalida[]= {
  &PTT+1,1,5,
  &PTT+1,1<<1,2, 
  &PTT+1,1<<2,6,
  &PTT+1,1<<3,4, 
  &PTT+1,1<<4,3,
  &PTT+1,1<<5,0,
  &PTT+1,1<<6,1,
  &PTT+1,1<<7,7
};


NEW_LEDS_SALIDA(ledsSalida,configuracionLedsSalida);

void ControlSD100_procesar(uchar tecla){
  int i;

  if(tecla == 'k'){
      for(i=0;i<CANTIDAD_SAL_ALARMA;i++) {
        
        AlarmaDeSensor_manejador(&alarma[i], tecla);
      }
  }
  
  DN_Proc(tecla);
}


void main(void){
  
  char tecla; 
  bool prevVal;
  byte i;
   
  newAlloced(&adquisidorSimple,&AdquisidorSimple,NULL,&flash);

  newAlloced(&termometro,&Termometro,&flash);
  com_initialization(&arrayNodosComunicacion);
 
  /*PWM0*/
  newAlloced(&pwmsTimer[0],&PWMTimer,&pwm_config[0],0);
  pwm[0]= &pwmsTimer[0];
  /*PWM1*/
  newAlloced(&pwmsTimer[1],&PWMTimer,&pwm_config[1],1);
  pwm[1]=&pwmsTimer[1]; 
  /*PWM2*/
  newAlloced(&pwmsTimer[2],&PWMTimer,&pwm_config[2],2);
  pwm[2]= &pwmsTimer[2];  
  /*PWM3*/
  newAlloced(&pwmsTimer[3],&PWMTimer,&pwm_config[3],3);
  pwm[3]=&pwmsTimer[3];
    
 
  
  for(i=0;i<CANTIDAD_SAL_ALARMA;i++)
    newAlloced(&alarma[i],AlarmaDeSensor,&alar_conf[i],&termometro.sensor[i],pwm[i]);


   
   //Conectar salidas dentro de SALIDA_TIEMPO_DESCONECTADA ms
   newAlloced(&timerConexionSalidas,&RlxMTimer,(ulong)SALIDA_TIEMPO_DESCONECTADA,SD100_conectarSalidas,NULL);
   
   //Diagrama de navegacion
   DN_staticInit(&OpList,&AccessList);


														 
  for(;;){
    tecla=get_key();  
    //Eventos    
    ControlSD100_procesar(tecla);
    mainLoop(&adquisidorSimple);
  }
}


void SD100_conectarSalidas(void * self){
  byte i;
  
  Timer_Stop(&timerConexionSalidas);
  
  for(i=0;i<CANTIDAD_SAL_ALARMA;i++)
    setConectada(pwm[i],TRUE);
  
   //configurar leds
   LedsSalida_init(&ledsSalida);

}
