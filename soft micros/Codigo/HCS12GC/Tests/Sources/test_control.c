/* TestControl.c*/
#include <stddef.h>

#include "Timer.h"
#include "display.h"
#include "WDog1.h"
#include "teclas.h"
#include "Class.h"
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
#include "RlxMTimer.h"
#include "Terminal.h"
#include "termio.h"
#include "hidef.h"
#include "stdio.h"

#define CNTR_TIME_DISCONECT 2000

#pragma CONST_SEG PARAMETERS_PAGE
volatile const TConfPWM pwm_config;
volatile const SensorConf sensor_config=STPT_DEF_CONF;
volatile const ControlConf pid_config=ControlDefaultConf; 
#pragma CONST_SEG DEFAULT

struct TSensor_TermoPT sensor;
struct PWM  pwm;
struct ControlPID pid; 
struct MessageOut msj1;
  
const struct BlockConstBoxPri1c CBox_Pri={
      BoxPri1c,							/* funcion que procesa al box*/
      &sensor,
      &msj1						
};

void OnTSalChange(void * self,int val){
  extern const struct ConstrGetterNum GetterPIDPot;
  extern const struct ConstPropNumPV ParSP;
  static Message msj_on_sal_change=NULL;
  
  if(val==_MAN){
    BoxPri1c_ShowGetter(&GetterPIDPot,&pid);			 // no muestro 
    if(!msj_on_sal_change)
      msj_on_sal_change=MessageOut_AddMessage(&msj1,"MAn ");    
  }else{
    BoxPri1c_ShowProp(&ParSP,&pid);
    if(msj_on_sal_change){
      MessageOut_DeleteMessage(&msj1,msj_on_sal_change);
      msj_on_sal_change=NULL;
    }
  }
}


void main (void){

  char tecla; 
  struct PropNum* prop;
  struct BoxCondl *_box;
  int val;
  struct TAdc  AD1;
  										 
  
  
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/
//  EnableInterrupts;
  TERMIO_Init(); /* Initialize communication on the pseudo terminal.*/
  TERM_Direct(TERM_APPEND_BOTH, "test.res"); /* Redirect output to the
//File test.res.*/
  printf ("Testing function Func\n");
  TERM_Direct(TERM_TO_WINDOW, ""); /* Remove redirection. */
  
  Teclas_Init();
  Display_Init(); // Inicializacion del display
  
  newAllocObj(&AD1,TAdc,0);
  newAllocObj(&sensor,TSensor_TermoPT,&AD1,&sensor_config,"Sen1");
  newAllocObj(&pwm,PWM,&pwm_config,0);
  newAllocObj(&pid,ControlPID,&pid_config,&sensor,&pwm,CNTR_TIME_DISCONECT);
  newAllocObj(&msj1,MessageOut); 
  
  
  PID_AddOnTSalChange(&pid,OnTSalChange,NULL);
  
  DN_InitSized(&CBox_Pri,5);
  Sets_Init2(4);
  DN_addBoxList(0,"tun ",7);
  DN_addBoxList(0,"CAL ",6);
  DN_addBoxList(0,"Set ",5); 
  DN_addBoxList(0,"Lim ",4);
  SnsHmi_Add(&sensor,0);
  PidHmi_AddBoxes(&pid,0);
  PWMHmi_addIndexedPeriodo(&pwm,0,"tun ",0,1);


// 	_Salida_setDuty(pwm,0);	
 														 
  for(;;){
    WDog1_Clear();
    tecla=get_key();  
    //Eventos
    SenTPT_Handler(&sensor);
    DN_Proc(tecla);
    RlxMTimer_Handler();
  }
}
