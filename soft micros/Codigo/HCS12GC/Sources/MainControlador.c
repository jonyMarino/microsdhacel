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
#include "Pid2SPHmi.h"
#include "ControlPID2SP.h"
#include "InpSP2.h"



#ifdef DOBLE_SET_POINT
  #define DECLARACION_CONF_CONTROL volatile const Control2SPConf pid_config=Control2SPDefaultConf 
	#define TIPO_CONTROL_1 struct ControlPID2SP
  #define CREAR_CONTROL_1() newAllocObj(&pid,ControlPID2SP,&pid_config,&sensor,&pwm[0],CNTR_TIME_DISCONECT,chk2SPPin)
  #define ADD_BOX_CONT1(numcontrol)   Pid2SPHmi_AddBoxes(&pid,numcontrol);
#else
  #define DECLARACION_CONF_CONTROL volatile const ControlConf pid_config=ControlDefaultConf 
	#define TIPO_CONTROL_1 struct ControlPID
  #define CREAR_CONTROL_1()   newAllocObj(&pid,ControlPID,&pid_config,&sensor,&pwm[0],CNTR_TIME_DISCONECT)
  #define ADD_BOX_CONT1(numcontrol)   PidHmi_AddBoxes(&pid,numcontrol);
#endif

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
DECLARACION_CONF_CONTROL;
volatile const TAlarmaConf alar_conf=ALARMA_DEFAULT_CONF; 
#pragma CONST_SEG DEFAULT

struct TSensor_TermoPT sensor;
struct PWM  pwm[NUM_SALIDAS];
TIPO_CONTROL_1 pid; 
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

#ifdef DOBLE_SET_POINT
  InpSP2_Init();
  prevVal =InpSP2_GetVal();  

#endif  

  newAllocObj(&AD1,TAdc,0);
  newAllocObj(&sensor,TSensor_TermoPT,&AD1,&sensor_config,"Sen1");
  newAllocObj(&pwm[0],PWM,&pwm_config[0],OUT_CNTR_1);
  newAllocObj(&pwm[1],PWM,&pwm_config[1],OUT_AL_1);
  CREAR_CONTROL_1();
  newAllocObj(&alarma,AlarmaMult,&alar_conf,&pid,&pwm[1],AL_TIME_DISCONECT);
  newAllocObj(&msj1,MessageOut); 
  
  
  PID_AddOnTSalChange(&pid,OnTSalChange,NULL);
  
  DN_InitSized(&CBox_Pri,5);
  Sets_Init2(4);
  DN_addBoxList(0,"tun ",7);
  DN_addBoxList(0,"CAL ",6);
  DN_addBoxList(0,"Set ",5); 
  DN_addBoxList(0,"Lim ",4);
  SnsHmi_Add(&sensor,0);
  ADD_BOX_CONT1(0);
  AlarmasHmi_AddBoxes(&alarma,0);
  PWMHmi_addIndexedPeriodo(&pwm[0],0,"tun ",0,1);  
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
    SenTPT_Handler(&sensor);

#ifdef DOBLE_SET_POINT
    if(prevVal != InpSP2_GetVal()){
      prevVal =InpSP2_GetVal();
      DN_Refresh();
    }
#endif  



    DN_Proc(tecla);
    com_Handler();
    AL_Handler(&alarma,tecla);
  }
}

