#include "Termometro.h"
#include "FlashBkpEnFlash.h"
#include "PWM.h"
#include "AlarmaDeSensor.h"
#include "BoxPrincipalNC.h"
#include "display.h"
#include "timer_interrupt.h"
#include "DiagramaNavegacion.h"
#include "Sets.h"
#include "SnsHmi.h"
#include "AlarmaDeSensorHmi.h"
#include "ModBusHmi.h"
#include "teclas.h"
#include "PWMTimer.h"
					
#define CNTR_TIME_DISCONECT 3000   //tiene que alcanzar para hacer 2 mediciones
#define AL_TIME_DISCONECT 2000 


#pragma CONST_SEG PARAMETERS_PAGE
volatile const ConfiguracionTermometro termometro_config={
    STPT_DEF_CONF,							
    STPT_DEF_CONF,						
    STPT_DEF_CONF,				
    STPT_DEF_CONF				

};

volatile const TConfPWM pwm_config[CANTIDAD_SAL_ALARMA];

volatile const TAlarmaConf alar_conf[CANTIDAD_SAL_ALARMA]={
    ALARMA_DEFAULT_CONF,
    ALARMA_DEFAULT_CONF,
    ALARMA_DEFAULT_CONF,
    ALARMA_DEFAULT_CONF
};
#pragma CONST_SEG DEFAULT

struct Termometro termometro;
struct PWMTimer  pwm[CANTIDAD_SAL_ALARMA];
struct AlarmaDeSensor alarma[CANTIDAD_SAL_ALARMA];

const struct getter * gettersAMostrar[]={
  &termometro.sensor[0],
  &termometro.sensor[1],
  &termometro.sensor[2],
  &termometro.sensor[3]
};					

const struct BlockConstBoxPriNC CBox_Pri={
      BoxPriNC,							/* funcion que procesa al box*/
      gettersAMostrar,      
      NULL						
};


NEW_FLASH_BKP_EN_FLASH(flash,0x4200);

void main(void){
  byte i;
  newAllocObj(&termometro,Termometro,&termometro_config,&flash);
  
  for(i=0;i<CANTIDAD_SAL_ALARMA;i++)
    newAllocObj(&pwm[i],PWMTimer,&pwm_config[i],i);
    
  for(i=0;i<CANTIDAD_SAL_ALARMA;i++)
    newAllocObj(&alarma[i],AlarmaDeSensor,&alar_conf[i],&termometro.sensor[i],&pwm[i],AL_TIME_DISCONECT);

  add1msListener(DpyAndSwitch,NULL);
  
  DN_InitSized(&CBox_Pri,5);
  Sets_Init2(4);
  DN_addBoxList(0,"tun ",(CANTIDAD_SAL_ALARMA+1));
  DN_addBoxList(0,"CAL ",(CANTIDAD_CANALES+1));
  DN_addBoxList(0,"Set ",1+(CANTIDAD_SAL_ALARMA+1)); 

  for(i=0;i<CANTIDAD_CANALES;i++)
    SnsHmi_Add(&termometro.sensor[i],i+1);
  for(i=0;i<CANTIDAD_SAL_ALARMA;i++)
    AlarmaDeSensorHmi_AddBoxes(&alarma[i],i+1);  
  Sets_AddBoxes();
  ModBusHmi_AddBoxes();

  for(;;){
    byte tecla=get_key();      
    DN_Proc(tecla);
    
    Termometro_mainLoop(&termometro);
    
    for(i=0;i<CANTIDAD_SAL_ALARMA;i++)
      AlarmaDeSensor_manejador(&alarma[i],tecla);
    RlxMTimer_Handler();  
  }
  
}