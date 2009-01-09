/* TestControl.c*/
#include <stddef.h>

#include "Timer.h"
#include "display.h"
#include "WDog1.h"
#include "teclas.h"
#include "Class.h"
#include "ClassADC.h"
#include "Grabacion.h"
#include "PWM_Class.h"
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
#include "Alarmas.h"
#include "AlarmasHmi.h"
#include "ModBusHmi.h"
#include "com_events.h"
#include "ControlPID2SP.h"
#include "Pid2SPHmi.h"
#include "InpSP2.h"


/*  Tiempo inicial en el que el control permanece desconectado  */
#ifdef _COLADA_CALIENTE  
  #define CNTR_TIME_DISCONECT 20000 
#else
  #define CNTR_TIME_DISCONECT 3000   //tiene que alcanzar para hacer 2 mediciones
#endif

#define AL_TIME_DISCONECT 2000 

volatile const long SerialNum@0x4000;

#pragma CONST_SEG PARAMETERS_PAGE
volatile const TConfPWM pwm_config[NUM_SALIDAS];
volatile const SensorConf sensor_config=STPT_DEF_CONF;
volatile const Control2SPConf pid_config=ControlDefaultConf; 
volatile const TAlarmaConf alar_conf=ALARMA_DEFAULT_CONF; 
#pragma CONST_SEG DEFAULT

struct TSensor_TermoPT sensor;
struct PWM  pwm[NUM_SALIDAS];
struct ControlPID2SP pid; 
struct MessageOut msj1;
struct TAdc  AD1;
struct AlarmaMult alarma;

    
const struct BlockConstBoxPri1c CBox_Pri={
      BoxPri1c,							/* funcion que procesa al box*/
      &sensor,
      &msj1						
};

void OnTSalChange(void * self,int val){
  extern const struct ConstrGetterNum GetterPIDPot;
  extern const struct ConstPropNumPV ParSPOP;
  static Message msj_on_sal_change=NULL;
  
  if(val==_MAN){
    BoxPri1c_ShowGetter(&GetterPIDPot,&pid);			 // no muestro 
    if(!msj_on_sal_change)
      msj_on_sal_change=MessageOut_AddMessage(&msj1,"MAn ");    
  }else{
    BoxPri1c_ShowProp(&ParSPOP,&pid);
    if(msj_on_sal_change){
      MessageOut_DeleteMessage(&msj1,msj_on_sal_change);
      msj_on_sal_change=NULL;
    }
  }
}
bool chk2SPPin(void){
  return (InpSP2_GetVal());
}

void main (void){

  char tecla; 
  bool prevVal;
  
  
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/
 
  Teclas_Init();
  Display_Init(); // Inicializacion del display
  com_Init();
  InpSP2_Init();
 
  prevVal =InpSP2_GetVal();  
  
  newAllocObj(&AD1,TAdc,0);
  newAllocObj(&sensor,TSensor_TermoPT,&AD1,&sensor_config);
  newAllocObj(&pwm[0],PWM,&pwm_config[0],OUT_CNTR_1);
  newAllocObj(&pwm[1],PWM,&pwm_config[1],OUT_AL_1);
  newAllocObj(&pid,ControlPID2SP,&pid_config,&sensor,&pwm[0],CNTR_TIME_DISCONECT, chk2SPPin);
  newAllocObj(&alarma,AlarmaMult,&alar_conf,&pid,&pwm[1],AL_TIME_DISCONECT);

  newAllocObj(&msj1,MessageOut); 
  
  
  PID_AddOnTSalChange(&pid,OnTSalChange,NULL);
  
  DN_Init(&CBox_Pri);
  Sets_Init();
  PWM_Hmi_Add(&pwm[0],0);
  SnsHmi_Add(&sensor,0);
  Pid2SPHmi_AddBoxes(&pid,0);
  AlarmasHmi_AddBoxes(&alarma,0);
  Sets_AddBoxes();
  ModBusHmi_AddBoxes();
  
  PwmHmi_ComuAdd(&pwm[0],1000);
 	PwmHmi_ComuAdd(&pwm[1],1020);
 	SnsHmi_ComuAdd(&sensor,1040);
 	PidHmi_ComuAdd(&pid,1060);
 	AlarmasHmi_ComuAdd(&alarma,1080);
 	ModBusHmi_ComuAdd(1100);
 														 
  for(;;){
    WDog1_Clear();
    tecla=get_key();  
    //Eventos
    if(prevVal != InpSP2_GetVal()){
      prevVal =InpSP2_GetVal();
      DN_Refresh();
    }
    SenTPT_Handler(&sensor);
    DN_Proc(tecla);
    com_Handler();
    AL_Handler(&alarma,tecla);
  }
}

