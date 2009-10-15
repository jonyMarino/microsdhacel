#include "Timer.h"
#include "display.h"
#include "WDog1.h"
#include "teclas.h"
#include "Object.h"
#include "PWMTimer.h"
#include "DiagramaNavegacion.h"
#include "Sets.h"
#include "PWM_Hmi.h"
#include "Grabacion.h"
#include "CapturadorPT2.h"
#include "ThreadAdjuntable.h"
#include "SensorRPM.h"
#include "CapturadorSimulado.h"
#include "ControlPID.h"
#include "PidHmi.h"
#include "PropNumPV.h"
#include "MessagesOut.h"
#include "SenRpmHmi.h"
#include "FlashBkp256.h"
#include "TI1.h"
#include "timer_interrupt.h"
#include "PlataformaEmbedded.h"
#include "FstBoxPointer.h"
#include "BoxList.h"
#include "ModBusHmi.h"
#include "NodoICModBus.h"
#include "ArrayList.h"
#include "Access.h"
#include "com_events.h"
#include "LedsSalida.h"

#pragma CONST_SEG PARAMETERS_PAGE
volatile const SensorRpmConf config=DEFAULT_SENSOR_RPM_CONF;
volatile const TConfPWM pwm_config={
  9
};
volatile const ControlConf pid_config=ControlDefaultConf; 
#pragma CONST_SEG DEFAULT
struct PWMTimer  pwm;
struct ControlPID pid; 
static struct MessageOut msj[CANTIDAD_SAL_CONTROL];
struct Capturador * cap;
struct ThreadAdjuntable mainThread;
struct SensorRpm sensorRpm;

/*  COMUNICACION  */
  /*PWM*/
  static const NEW_NODO_IC_MODBUS(PWM1Com,&PWM_GETTERS_ARRAY,1000,&pwm);
  static const NEW_NODO_IC_MODBUS(PWM5Com,&PWM_GETTER_POT_ARRAY,1041,&pwm);

  /*Sensor*/
  static const NEW_NODO_IC_MODBUS(Sen1Com,&arraySenGetters,1100,&sensorRpm);


  /*Alarma*/
//  static const NEW_NODO_IC_MODBUS(Al1Com,&AL_GETTERS_ARRAY,1200,&alarma[0]);
  /*PID*/
  static const NEW_NODO_IC_MODBUS(Pid1Com,&PID_GETTERS_ARRAY,1300,&pid);
  /*Comunicacion*/
  static const NEW_NODO_IC_MODBUS(ModBusCom,&MODBUS_GETTERS_ARRAY,1400,NULL);
  /*Codigo*/
  static const NEW_NODO_IC_MODBUS(CodCom,&COD_GETTERS_ARRAY,1500,NULL);


  static const struct NodoICModBus *const  nodosComunicacion[]={
     //Pwm
     &PWM1Com,
       &PWM5Com,
     //Sensor
     &Sen1Com,
      //Alarma
//     &Al1Com,
     //Pid
     &Pid1Com,
     //Comunicacion
     &ModBusCom,    
     //codigo
     &CodCom
  };
  static const NEW_ARRAY_LIST(arrayNodosComunicacion,nodosComunicacion);
/*  FIN COMUNICACION  */
/*  Diagrama de navegacion  */

#ifdef HD90
const struct BlockConstBoxPri CBox_Pri={
      &BoxPri,							/* funcion que procesa al box*/
#else  
const struct BlockConstBoxPri1c CBox_Pri={
      &BoxPri1c,							/* funcion que procesa al box*/
#endif
      &sensorRpm,
      msj						
};


//Operador
  //Principal
static const NEW_FST_BOX_POINTER(Principal,&CBox_Pri,NULL,0);
  //Control
static const NEW_FST_BOX_POINTER(Cntrl1OP1,&PID_HMI_FST_OP_BOX,&pid,0);
static const NEW_FST_BOX_POINTER(Cntrl1OP2,&PID_HMI_SCND_OP_BOX,&pid,0);
  //Alarma
//static const NEW_FST_BOX_POINTER(AL1OP,&ALARMA_DE_SENSOR_HMI_FST_OP,&alarma[0],0);

 
static const struct FstBoxPointer *const OpArray[]={
  &Principal,
  &Cntrl1OP1,
  &Cntrl1OP2,    
 // &AL1OP,  
  
};


static const NEW_BOX_LIST(OpList,OpArray,"op");



//CAL
static const NEW_FST_BOX_POINTER(Sensor1List,&CBox_SenRpm,&sensorRpm,0);
  
static const struct FstBoxPointer *const CalArray[]={
  &Sensor1List   
};

static const NEW_BOX_LIST(Cal,CalArray,"rPM");

//TUN
static const NEW_FST_BOX_POINTER(Cntrl1Tun1,&PID_HMI_FST_TUN_BOX,&pid,0);
static const NEW_FST_BOX_POINTER(Cntrl1Tun2,&PID_HMI_SCND_TUN_BOX,&pid,0);
static const NEW_FST_BOX_POINTER(PWM1Tun,&PWM_VISTA_FST_TUN_BOX,&pwm,0);


  //Alarma
//static const NEW_FST_BOX_POINTER(AL1TUN,&ALARMA_DE_SENSOR_HMI_FST_TUN,&alarma[0],0);
  
static const struct FstBoxPointer *const TunArray[]={
  &Cntrl1Tun1, 
  &PWM1Tun,
  &Cntrl1Tun2, 
  //&AL1TUN,
};

static const NEW_BOX_LIST(Tun,TunArray,"tun");

//SET
  //Control
static const NEW_FST_BOX_POINTER(Cntrl1Set,&PID_HMI_FST_SET_BOX,&pid,0);

  //Alarma
//static const NEW_FST_BOX_POINTER(AL1SET,&ALARMA_DE_SENSOR_HMI_FST_SET,&alarma[0],0);

  //Comunicacion
static const NEW_FST_BOX_POINTER(ModBusSet,&MOD_BUS_HMI_FST_BOX_SET,0,0);
  //SetC
static const NEW_FST_BOX_POINTER(SetsSet,&SETS_FST_BOX_SET,0,0);
  

static const struct FstBoxPointer *const SetArray[]={
  &Cntrl1Set, 
 // &AL1SET,
  &ModBusSet,
  &SetsSet  
};

static const NEW_BOX_LIST(Set,SetArray,"SEt");

//LIM
static const NEW_FST_BOX_POINTER(Cntrl1Lim,&PID_HMI_FST_LIM_BOX,&pid,0);

static const struct FstBoxPointer *const LimArray[]={
  &Cntrl1Lim 
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


#ifndef HD90
void OnTSalChange(void * self,int val){
  extern const struct ConstrGetterNum GetterPIDPot;
  extern const struct ConstPropNumPV ParSP;
  static Message msj_on_sal_change=NULL;
  
  if(val==_MAN){
    BoxPri1c_ShowGetter(&GetterPIDPot,&pid);			 // no muestro 
    if(!msj_on_sal_change)
      msj_on_sal_change=MessageOut_AddMessage(&msj[0],"MAn ");    
  }else{
    BoxPri1c_ShowProp(&ParSP,&pid);
    if(msj_on_sal_change){
      MessageOut_DeleteMessage(&msj[0],msj_on_sal_change);
      msj_on_sal_change=NULL;
    }
  }
}  
#endif

//#define _ENTRADA_SIMULADA

#ifdef _ENTRADA_SIMULADA
  #define GET_INSTANCE() CapturadorSimulado_getInstancia()
#else
  #define GET_INSTANCE() CapturadorPT2_getInstancia()
#endif

#define CNTR_TIME_DISCONECT	 2000

struct PlataformaEmbedded plataforma;


NEW_FLASH_BKP_256(flash,0x4400);
struct ManejadorMemoria *const pFlash=&flash;

void on1ms(void * termometro){
   
    if(PromBkp_listoParaGrabarOBorrar(&flash))
      TI1_SetPeriodMode(TI1_Pm_40ms);
    
    DpyAndSwitch();
}

void on40ms(void * termometro){
    (void)TI1_SetPeriodMode(TI1_Pm_1ms); //Next interrupt is 1ms length

    PromBkp_grabarOBorrar(&flash);

   
}

const LedConfig configuracionLedsSalida[]= {
  &PTT+1,1,0,
//  &PTT+1,1<<1,1, 
//  &PTT+1,1<<2,2,
//  &PTT+1,1<<3,3, 
};


NEW_LEDS_SALIDA(ledsSalida,configuracionLedsSalida);


void main (void){
  char tecla;
   
  
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/
  newAlloced(&plataforma,&PlataformaEmbedded);
  Teclas_Init();
  Display_Init(); // Inicializacion del display
  com_initialization(&arrayNodosComunicacion);
  
  add1msListener(_new(&Method,on1ms,0));
  add40msListener(_new(&Method,on40ms,0));
  
  newAlloced(&mainThread,&ThreadAdjuntable);
  cap=GET_INSTANCE();
  #ifdef _ENTRADA_SIMULADA
  CapturadorSimulado_setMicroSegundos(cap,100000000);
  CapturadorSimulado_setPulsos(cap,2);
  #endif
  {
    void * adjuntador= ThreadAdjuntable_getAdjuntador(&mainThread);
    newAlloced(&sensorRpm,&SensorRpm,adjuntador,1000,cap,&config,"SEn rPM");
    _delete(adjuntador);
  }
  newAlloced(&pwm,&PWMTimer,&pwm_config,0);
  newAlloced(&pid,ControlPID,&pid_config,&sensorRpm,&pwm);
  newAlloced(&msj[0],MessageOut); 
  
  #ifndef HD90
  PID_AddOnTSalChange(&pid,OnTSalChange,NULL);
  #endif
  
  /*
  DN_Init(&CBox_Pri);
  Sets_Init();
  PWM_Hmi_Add(&pwm,0);
  SenRpmHmi_Add(&sensorRpm,0);
  PidHmi_AddBoxes(&pid,0);

//  PidHmi_AddBoxes(&pid,2);
//  PidHmi_AddBoxes(&pid,3);
  Sets_AddBoxes();   */
  
  DN_staticInit(&OpList,&AccessList);
  
  setConectada(&pwm,TRUE);
  LedsSalida_init(&ledsSalida);
 	
 	  														 
  for(;;){
    WDog1_Clear();
    tecla=get_key();  
    
    //Eventos
    MethodContainer_execute(&mainThread);
    mainLoop(&plataforma);
   
    
    DN_Proc(tecla);
  }
}