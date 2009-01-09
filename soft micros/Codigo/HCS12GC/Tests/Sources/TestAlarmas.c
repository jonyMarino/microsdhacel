/* TestAlarmas.c*/
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
#include "alarmas.h"
#include "AlarmasHmi.h"
#include "RlxMTimer.h"


/*  Tiempo inicial en el que el control permanece desconectado  */
#ifdef _COLADA_CALIENTE  
  #define CNTR_TIME_DISCONECT 20000 
#else
  #define CNTR_TIME_DISCONECT 3000   //tiene que alcanzar para hacer 2 mediciones
#endif

#define AL_TIME_DISCONECT 2000 



#pragma CONST_SEG PARAMETERS_PAGE
volatile const TConfPWM pwm_config[NUM_SALIDAS];
volatile const SensorConf sensor_config=STPT_DEF_CONF;
volatile const ControlConf pid_config=ControlDefaultConf;
volatile const TAlarmaConf alar_conf=ALARMA_DEFAULT_CONF; 
#pragma CONST_SEG DEFAULT

struct TSensor_TermoPT sensor;
struct PWM  pwm[NUM_SALIDAS];
struct TAdc  AD1;
struct ControlPID pid; 
struct AlarmaMult alarma;
char tecla; 
    
const struct BlockConstBoxPri CBox_Pri={
  BoxPri,							/* funcion que procesa al box*/
  &sensor						
};



void main (void){
  
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/

  Teclas_Init();
  Display_Init(); // Inicializacion del display

  newAllocObj(&AD1,TAdc,0);
  newAllocObj(&sensor,TSensor_TermoPT,&AD1,&sensor_config);
  newAllocObj(&pwm[0],PWM,&pwm_config[0],OUT_CNTR_1);
  newAllocObj(&pwm[1],PWM,&pwm_config[1],OUT_AL_1); 
  newAllocObj(&pid,ControlPID,&pid_config,&sensor,&pwm[0],CNTR_TIME_DISCONECT);
  newAllocObj(&alarma,AlarmaMult,&alar_conf,&pid,&pwm[1],AL_TIME_DISCONECT);
  
//  DN_Init(&CBox_Pri);
  DN_InitSized(&CBox_Pri,5);
  Sets_Init2(4);
  DN_addBoxList(0,"tun ",7);
  DN_addBoxList(0,"CAL ",6);
  DN_addBoxList(0,"Set ",5); 
  DN_addBoxList(0,"Lim ",4);
  SnsHmi_Add(&sensor,0);
  PidHmi_AddBoxes(&pid,0);
  PWMHmi_addIndexedPeriodo(&pwm,0,"tun ",0,1);
  AlarmasHmi_AddBoxes(&alarma,0);
  Sets_AddBoxes();

 														 
  for(;;){
    WDog1_Clear();
    tecla=get_key();  
    //Eventos
    SenTPT_Handler(&sensor);
    AL_Handler(&alarma,tecla);
    DN_Proc(tecla);
    RlxMTimer_Handler();

  }
}