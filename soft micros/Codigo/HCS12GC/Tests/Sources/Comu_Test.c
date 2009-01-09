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
#include "Terminal.h"
#include "termio.h"
#include "hidef.h"
#include "stdio.h"
#include "com_events.h"
#include "ModBusHmi.h"

#define CNTR_TIME_DISCONECT 2000

#pragma CONST_SEG PARAMETERS_PAGE
volatile const TConfPWM pwm_config;
volatile const SensorConf sensor_config=STPT_DEF_CONF;
volatile const ControlConf pid_config=ControlDefaultConf; 
#pragma CONST_SEG DEFAULT

struct TSensor_TermoPT sensor;
  
const struct BlockConstBoxPri CBox_Pri={
      BoxPri,							/* funcion que procesa al box*/
      &sensor						
};


void main (void){

  char tecla; 
  struct PropNum* prop;
  struct BoxCondl *_box;
  int val;
  struct PWM  pwm;
  struct TAdc  AD1;

  struct ControlPID pid; 
  
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/
//  EnableInterrupts;
//  TERMIO_Init(); /* Initialize communication on the pseudo terminal.*/
//  TERM_Direct(TERM_APPEND_BOTH, "test.res"); /* Redirect output to the
//File test.res.*/
//  printf ("Testing function Func\n");
  Teclas_Init();
  Display_Init(); // Inicializacion del display

  newAllocObj(&AD1,TAdc,0);
  newAllocObj(&sensor,TSensor_TermoPT,&AD1,&sensor_config);
  newAllocObj(&pwm,PWM,&pwm_config,0);
  newAllocObj(&pid,ControlPID,&pid_config,&sensor,&pwm,CNTR_TIME_DISCONECT);
  
  
  DN_Init(&CBox_Pri);
  Sets_Init();
  PWM_Hmi_Add(&pwm,0);
  SnsHmi_Add(&sensor,0);
  PidHmi_AddBoxes(&pid,0);
  Sets_AddBoxes();
  ModBusHmi_AddBoxes();
  
  com_Init();
  SnsHmi_ComuAdd(&sensor,1000);
  ModBusHmi_ComuAdd(1050);	
 														 
  for(;;){
    WDog1_Clear();
    tecla=get_key();  
    //Eventos
    SenTPT_Handler(&sensor);
    DN_Proc(tecla);
    com_Handler();
  }
}