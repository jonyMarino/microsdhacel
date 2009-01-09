
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
#include "PWMTimer.h"
#include "PWMSoft.h"
#include "FstBoxPointer.h"
#include "BoxList.h"
#include "Access.h"
#include "AlarmaControl.h"
#include "RlxMTimer.h"
#include "LedsSalida.h"
#include "ThreadAdjuntable.h"
#include "Thread.h"
#include "AlarmaControlVista.h"
#include "PWMPeriodoEvent.h"
#include "SensorSimulado.h"

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

#pragma CONST_SEG PARAMETERS_PAGE
volatile const TConfPWM pwm_config[CANTIDAD_SAL_ALARMA+CANTIDAD_SAL_CONTROL];
volatile const ConfiguracionTermometro termometro_config={
  STPT_DEF_CONF,
  #if CANTIDAD_CANALES>1 
    STPT_DEF_CONF,
      #if CANTIDAD_CANALES>2
        STPT_DEF_CONF,
        #if CANTIDAD_CANALES>3
          STPT_DEF_CONF
        #endif
      #endif
  #endif
};

volatile const ControlConf control_conf[CANTIDAD_SAL_CONTROL]={
  //ControlDefaultConf,
  100,															
  0,															
  1700,														
  0,															
  10,														
  CNTR_PID,											
	_CAL,														
	0,															
	0,															
	0,															
	1000,														
	0, 															

  #if CANTIDAD_SAL_CONTROL>1 
  200,															
  0,															
  1700,														
  0,															
  10,														
  CNTR_PID,											
	_CAL,														
	0,															
	0,															
	0,															
	1000,														
	0,
      #if CANTIDAD_SAL_CONTROL>2
  300,															
  0,															
  1700,														
  0,															
  10,														
  CNTR_PID,											
	_CAL,														
	0,															
	0,															
	0,															
	1000,														
	0,
        #if CANTIDAD_SAL_CONTROL>3
  400,															
  0,															
  1700,														
  0,															
  10,														
  CNTR_PID,											
	_CAL,														
	0,															
	0,															
	0,															
	1000,														
	0,
        #endif
      #endif
  #endif
};

volatile const struct AlarmaCntrConf alar_conf[CANTIDAD_SAL_ALARMA]={
//ALarma1
0,    //RET
100,  //RET
ALARMA_CONTROL,
SALIDA_EXCESO,
10,           //H
SALIDA_PROPORCIONAL,
10, //AL
CONTROL_RELATIVO,
//ALarma12
0,    //RET
100,  //RET
ALARMA_CONTROL,
SALIDA_EXCESO,
10,           //H
SALIDA_PROPORCIONAL,
20, //AL
CONTROL_RELATIVO,
//ALarma3
0,    //RET
100,  //RET
ALARMA_CONTROL,
SALIDA_EXCESO,
10,           //H
SALIDA_PROPORCIONAL,
30, //AL
CONTROL_RELATIVO,
//ALarma14
0,    //RET
100,  //RET
ALARMA_CONTROL,
SALIDA_EXCESO,
10,           //H
SALIDA_PROPORCIONAL,
40, //AL
CONTROL_RELATIVO,
};

#pragma CONST_SEG DEFAULT



struct PWM * pwm[CANTIDAD_SAL_ALARMA+CANTIDAD_SAL_CONTROL];
struct PWMPeriodoEvent pwmConEventoPeriodo[CANTIDAD_SAL_CONTROL];
struct TAdc  AD1[CANTIDAD_CANALES];
struct AlarmaControl alarma[CANTIDAD_SAL_ALARMA];
struct ControlPID control[CANTIDAD_SAL_CONTROL]; 

struct PWMTimer pwmsTimer[7];
struct PWMSoft pwmSoft;
           
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
  static const NEW_NODO_IC_MODBUS(PWM1Com,&PWM_GETTERS_ARRAY,1000,&pwmConEventoPeriodo[0]);
  static const NEW_NODO_IC_MODBUS(PWM2Com,&PWM_GETTERS_ARRAY,1010,&pwmConEventoPeriodo[1]);
  static const NEW_NODO_IC_MODBUS(PWM3Com,&PWM_GETTERS_ARRAY,1020,&pwmConEventoPeriodo[2]);
  static const NEW_NODO_IC_MODBUS(PWM4Com,&PWM_GETTERS_ARRAY,1030,&pwmConEventoPeriodo[3]);
  static const NEW_NODO_IC_MODBUS(PWM5Com,&PWM_GETTER_POT_ARRAY,1041,&pwmsTimer[4]);
  static const NEW_NODO_IC_MODBUS(PWM6Com,&PWM_GETTER_POT_ARRAY,1051,&pwmsTimer[5]);
  static const NEW_NODO_IC_MODBUS(PWM7Com,&PWM_GETTER_POT_ARRAY,1061,&pwmsTimer[6]);
  static const NEW_NODO_IC_MODBUS(PWM8Com,&PWM_GETTER_POT_ARRAY,1071,&pwmSoft);
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
  /*PID*/
  static const NEW_NODO_IC_MODBUS(Pid1Com,&PID_GETTERS_ARRAY,1300,&control[0]);
  static const NEW_NODO_IC_MODBUS(Pid2Com,&PID_GETTERS_ARRAY,1320,&control[1]);
  static const NEW_NODO_IC_MODBUS(Pid3Com,&PID_GETTERS_ARRAY,1340,&control[2]);
  static const NEW_NODO_IC_MODBUS(Pid4Com,&PID_GETTERS_ARRAY,1360,&control[3]);
  /*Comunicacion*/
  static const NEW_NODO_IC_MODBUS(ModBusCom,&MODBUS_GETTERS_ARRAY,1400,NULL);
  /*Codigo*/
  static const NEW_NODO_IC_MODBUS(CodCom,&COD_GETTERS_ARRAY,1500,NULL);


  static const struct NodoICModBus *const  nodosComunicacion[]={
     //Pwm
     &PWM1Com,
     &PWM2Com,
     &PWM3Com,
     &PWM4Com,
     &PWM5Com,
     &PWM6Com,
     &PWM7Com,
     &PWM8Com,
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
     //Pid
     &Pid1Com,
     &Pid2Com,
     &Pid3Com,
     &Pid4Com,             
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
static const NEW_FST_BOX_POINTER(Cntrl1OP1,&PID_HMI_FST_OP_BOX,&control[0],1);
static const NEW_FST_BOX_POINTER(Cntrl1OP2,&PID_HMI_SCND_OP_BOX,&control[0],1);
static const NEW_FST_BOX_POINTER(Cntrl2OP1,&PID_HMI_FST_OP_BOX,&control[1],2);
static const NEW_FST_BOX_POINTER(Cntrl2OP2,&PID_HMI_SCND_OP_BOX,&control[1],2);
static const NEW_FST_BOX_POINTER(Cntrl3OP1,&PID_HMI_FST_OP_BOX,&control[2],3);
static const NEW_FST_BOX_POINTER(Cntrl3OP2,&PID_HMI_SCND_OP_BOX,&control[2],3);
static const NEW_FST_BOX_POINTER(Cntrl4OP1,&PID_HMI_FST_OP_BOX,&control[3],4);
static const NEW_FST_BOX_POINTER(Cntrl4OP2,&PID_HMI_SCND_OP_BOX,&control[3],4);
  //Alarma
static const NEW_FST_BOX_POINTER(AL1OP,&ALARMA_DE_SENSOR_HMI_FST_OP,&alarma[0],1);
static const NEW_FST_BOX_POINTER(AL2OP,&ALARMA_DE_SENSOR_HMI_FST_OP,&alarma[1],2);
static const NEW_FST_BOX_POINTER(AL3OP,&ALARMA_DE_SENSOR_HMI_FST_OP,&alarma[2],3);
static const NEW_FST_BOX_POINTER(AL4OP,&ALARMA_DE_SENSOR_HMI_FST_OP,&alarma[3],4);
  

static const struct FstBoxPointer *const OpArray[]={
  &Principal,
  &Cntrl1OP1,
  &Cntrl2OP1,
  &Cntrl3OP1,
  &Cntrl4OP1,
  &Cntrl1OP2,    
  &Cntrl2OP2,   
  &Cntrl3OP2,   
  &Cntrl4OP2,
  &AL1OP,  
  &AL2OP, 
  &AL3OP,
  &AL4OP,  
};


static const NEW_BOX_LIST(OpList,OpArray,"op");

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
static const NEW_FST_BOX_POINTER(Cntrl1Tun1,&PID_HMI_FST_TUN_BOX,&control[0],1);
static const NEW_FST_BOX_POINTER(Cntrl1Tun2,&PID_HMI_SCND_TUN_BOX,&control[0],1);
static const NEW_FST_BOX_POINTER(Cntrl2Tun1,&PID_HMI_FST_TUN_BOX,&control[1],2);
static const NEW_FST_BOX_POINTER(Cntrl2Tun2,&PID_HMI_SCND_TUN_BOX,&control[1],2);
static const NEW_FST_BOX_POINTER(Cntrl3Tun1,&PID_HMI_FST_TUN_BOX,&control[2],3);
static const NEW_FST_BOX_POINTER(Cntrl3Tun2,&PID_HMI_SCND_TUN_BOX,&control[2],3);
static const NEW_FST_BOX_POINTER(Cntrl4Tun1,&PID_HMI_FST_TUN_BOX,&control[3],4);
static const NEW_FST_BOX_POINTER(Cntrl4Tun2,&PID_HMI_SCND_TUN_BOX,&control[3],4);
static const NEW_FST_BOX_POINTER(PWM1Tun,&PWM_VISTA_FST_TUN_BOX,&pwmConEventoPeriodo[0],1);
static const NEW_FST_BOX_POINTER(PWM2Tun,&PWM_VISTA_FST_TUN_BOX,&pwmConEventoPeriodo[1],2); 
static const NEW_FST_BOX_POINTER(PWM3Tun,&PWM_VISTA_FST_TUN_BOX,&pwmConEventoPeriodo[2],3);
static const NEW_FST_BOX_POINTER(PWM4Tun,&PWM_VISTA_FST_TUN_BOX,&pwmConEventoPeriodo[3],4);


  //Alarma
static const NEW_FST_BOX_POINTER(AL1TUN,&ALARMA_DE_SENSOR_HMI_FST_TUN,&alarma[0],1);
static const NEW_FST_BOX_POINTER(AL2TUN,&ALARMA_DE_SENSOR_HMI_FST_TUN,&alarma[1],2);
static const NEW_FST_BOX_POINTER(AL3TUN,&ALARMA_DE_SENSOR_HMI_FST_TUN,&alarma[2],3);
static const NEW_FST_BOX_POINTER(AL4TUN,&ALARMA_DE_SENSOR_HMI_FST_TUN,&alarma[3],4);
  
static const struct FstBoxPointer *const TunArray[]={
  &Cntrl1Tun1, 
  &PWM1Tun,
  &Cntrl1Tun2, 
  &Cntrl2Tun1, 
  &PWM2Tun,
  &Cntrl2Tun2, 
  &Cntrl3Tun1,
  &PWM3Tun, 
  &Cntrl3Tun2, 
  &Cntrl4Tun1,
  &PWM4Tun, 
  &Cntrl4Tun2,
  &AL1TUN,
  &AL2TUN,
  &AL3TUN,
  &AL4TUN    
};

static const NEW_BOX_LIST(Tun,TunArray,"tun");

//SET
  //Control
static const NEW_FST_BOX_POINTER(Cntrl1Set,&PID_HMI_FST_SET_BOX,&control[0],1);
static const NEW_FST_BOX_POINTER(Cntrl2Set,&PID_HMI_FST_SET_BOX,&control[1],2);
static const NEW_FST_BOX_POINTER(Cntrl3Set,&PID_HMI_FST_SET_BOX,&control[2],3);
static const NEW_FST_BOX_POINTER(Cntrl4Set,&PID_HMI_FST_SET_BOX,&control[3],4);

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
  &Cntrl1Set, 
  &Cntrl2Set, 
  &Cntrl3Set, 
  &Cntrl4Set,
  &AL1SET,
  &AL2SET,
  &AL3SET,
  &AL4SET,
  &ModBusSet,
  &SetsSet  
};

static const NEW_BOX_LIST(Set,SetArray,"SEt");

//LIM
static const NEW_FST_BOX_POINTER(Cntrl1Lim,&PID_HMI_FST_LIM_BOX,&control[0],1);
static const NEW_FST_BOX_POINTER(Cntrl2Lim,&PID_HMI_FST_LIM_BOX,&control[1],2);
static const NEW_FST_BOX_POINTER(Cntrl3Lim,&PID_HMI_FST_LIM_BOX,&control[2],3);
static const NEW_FST_BOX_POINTER(Cntrl4Lim,&PID_HMI_FST_LIM_BOX,&control[3],4);

static const struct FstBoxPointer *const LimArray[]={
  &Cntrl1Lim, 
  &Cntrl2Lim, 
  &Cntrl3Lim, 
  &Cntrl4Lim  
};

static const NEW_BOX_LIST(Lim,LimArray,"Lim");

// Acceso comun
static const struct BoxList *const BoxListArray[]={
  &Tun,
  &Cal,
  &Set,
  &Lim
};

static const NEW_ACCESS(accesoComun,BoxListArray,"Cod",CONTENEDOR_CODIGO);

static const struct Access *const AccessArray[]={
  &accesoComun
};

static const NEW_ARRAY_LIST(AccessList,AccessArray);


/****************/


NEW_FLASH_BKP_EN_FLASH(flash,0x4400);
struct ManejadorMemoria *const pFlash= &flash;

void OnTSalChange(void * self, void * controlSender){
  extern const struct ConstrGetterNum GetterPIDPot;
  static Message msj_on_sal_change[CANTIDAD_SAL_CONTROL];
  int numControl= ((int)control - (int)controlSender)/sizeof(struct ControlPID) ;
  
  
  if(PID_getModSal(controlSender)==_MAN){
    if(!msj_on_sal_change[numControl])
      msj_on_sal_change[numControl]=MessageOut_AddMessage(&msj[numControl],"MAn ");    
  }else{
    if(msj_on_sal_change[numControl]){
      MessageOut_DeleteMessage(&msj[numControl],msj_on_sal_change[numControl]);
      msj_on_sal_change[numControl]=NULL;
    }
  } 
}

struct RlxMTimer timerConexionSalidas;

struct ThreadAdjuntable mainThread;

void pthread_create(void * _self,void * attr,void*(*pf)(void*),void* args){
  _self = new(&Method,pf,args);
  ThreadAdjuntable_Adjuntar(&mainThread,_self);  
}


const LedConfig configuracionLedsSalida[]= {
  &PTT+1,1,5,
  &PTT+1,1<<1,2, //Hard
  &PTT+1,1<<2,6,
  &PTT+1,1<<3,4, //Hard
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
        
        struct Lazo * lazo=_AlarmaControl_getLazo(&alarma[i]);
        if(instanceOf(lazo,&LazoAlarmaControl)){
          struct AdaptacionSalida * adaptador = _LazoControl_getAdaptadorSaldia(lazo);
          if(instanceOf(adaptador,&SalidaRetenida))
            SalidaRetenida_liberar((struct SalidaRetenida *)adaptador);   
        }
      }
  }
  
  DN_Proc(tecla);
}


void main (void){
  char tecla; 
  bool prevVal;
  byte i;
   

  newAlloced(&termometro,Termometro,&termometro_config,&flash);
  Teclas_Init();
  Display_Init(); // Inicializacion del display
  com_initialization(&arrayNodosComunicacion);

  add1msListener(DpyAndSwitch,NULL);

  //for(i=0;i<CANTIDAD_SAL_ALARMA+CANTIDAD_SAL_CONTROL;i++)
  //  newAlloced(&pwm[i],PWM,&pwm_config[i],i);
  /*PWM0*/
  newAlloced(&pwmsTimer[0],&PWMTimer,&pwm_config[0],0);
  newAlloced(&pwmConEventoPeriodo[0],&PWMPeriodoEvent,&pwmsTimer[0]);
  pwm[0]= &pwmConEventoPeriodo[0];
  /*PWM1*/
  newAlloced(&pwmsTimer[1],&PWMTimer,&pwm_config[1],1);
  newAlloced(&pwmConEventoPeriodo[1],&PWMPeriodoEvent,&pwmsTimer[1]);
  pwm[1]=&pwmConEventoPeriodo[1]; 
  /*PWM2*/
  newAlloced(&pwmsTimer[2],&PWMTimer,&pwm_config[2],2);
  newAlloced(&pwmConEventoPeriodo[2],&PWMPeriodoEvent,&pwmsTimer[2]);
  pwm[2]= &pwmConEventoPeriodo[2];  
  /*PWM3*/
  newAlloced(&pwmsTimer[3],&PWMTimer,&pwm_config[3],3);
  newAlloced(&pwmConEventoPeriodo[3],&PWMPeriodoEvent,&pwmsTimer[3]);
  pwm[3]=&pwmConEventoPeriodo[3];
  /*PWM4*/
  newAlloced(&pwmsTimer[4],&PWMTimer,&pwm_config[4],4);
  pwm[4]= &pwmsTimer[4];
  /*PWM5*/
  newAlloced(&pwmsTimer[5],&PWMTimer,&pwm_config[5],5);
  pwm[5]=&pwmsTimer[5]; 
  /*PWM6*/
  newAlloced(&pwmsTimer[6],&PWMTimer,&pwm_config[6],6);
  pwm[6]=&pwmsTimer[6];
  /*PWM7*/
  newAlloced(&pwmSoft,&PWMSoft,&pwm_config[7],&PTT,7); 
  pwm[7]=&pwmSoft;
  
  newAlloced(&mainThread,ThreadAdjuntable);
 
/*  {
    struct AdjuntadorAHilo* adj= ThreadAdjuntable_getAdjuntador(&mainThread);
    for(i=0;i<CANTIDAD_SAL_CONTROL+CANTIDAD_SAL_ALARMA;i++){      
      newAlloced(&sen[i],SensorSimulado,0,adj,1000,"Sen1");
      SensorSimulado_setValue(&sen[i],100);
    }
    deleteAndNil(&adj);
  }
  */
  
  for(i=0;i<CANTIDAD_SAL_CONTROL;i++)
    newAlloced(&control[i],ControlPID,&control_conf[i],&termometro.sensor[i],pwm[i]);

  for(i=0;i<CANTIDAD_SAL_ALARMA;i++)
    newAlloced(&alarma[i],&AlarmaControlClass,&alar_conf[i],&control[i],pwm[i+CANTIDAD_SAL_CONTROL]);

/* 
  for(i=0;i<CANTIDAD_SAL_CONTROL;i++){   
    newAlloced(&msj[i],MessageOut);
    PID_AddOnTSalChange(&control[i],OnTSalChange,NULL); 
  }
*/
   
   
   //Conectar salidas dentro de SALIDA_TIEMPO_DESCONECTADA ms
   newAlloced(&timerConexionSalidas,&RlxMTimer,(ulong)SALIDA_TIEMPO_DESCONECTADA,SD100_conectarSalidas,NULL);
   //configurar leds
   LedsSalida_init(&ledsSalida);
   
   //Diagrama de navegacion
   DN_staticInit(&OpList,&AccessList);
														 
  for(;;){
    tecla=get_key();  
    //Eventos
    
    ControlSD100_procesar(tecla);

    Termometro_mainLoop(&termometro);
    
    RlxMTimer_Handler();
    
    MethodContainer_execute(&mainThread);
//    for(i=0;i<CANTIDAD_SAL_ALARMA;i++)
//      AlarmaDeSensor_manejador(&alarma[i],tecla);
  }
}


void SD100_conectarSalidas(void * self){
  byte i;
  for(i=0;i<CANTIDAD_SAL_ALARMA+CANTIDAD_SAL_CONTROL;i++)
    setConectada(pwm[i],TRUE);
}



