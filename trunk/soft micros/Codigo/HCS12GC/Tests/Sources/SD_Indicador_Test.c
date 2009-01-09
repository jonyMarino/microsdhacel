
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
#include "AlarmaDeSensor.h"
#include "AlarmaDeSensorHmi.h"
#include "ModBusHmi.h"
#include "com_events.h"
#include "Pid2SPHmi.h"
#include "ControlPID2SP.h"
#include "InpSP2.h"
#include "BoxPrincipalNC.h"
#include "FlashBkpEnFlash.h"
#include "timer_interrupt.h"
#include "TI1.h"

/*  Tiempo inicial en el que el control permanece desconectado  */
#ifdef _COLADA_CALIENTE  
  #define CNTR_TIME_DISCONECT 20000 
#else
  #define CNTR_TIME_DISCONECT 3000   //tiene que alcanzar para hacer 2 mediciones
#endif

#define AL_TIME_DISCONECT 2000 

volatile const long SerialNum@0x4000;

#pragma CONST_SEG PARAMETERS_PAGE
volatile const TConfPWM pwm_config[CANTIDAD_SAL_ALARMA];
volatile const SensorConf sensor_config[CANTIDAD_CANALES]={
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

struct TSensor_TermoPT sensor[CANTIDAD_CANALES];
struct PWM  pwm[CANTIDAD_SAL_ALARMA];
//struct MessageOut msj1;
struct TAdc  AD1[CANTIDAD_CANALES];
struct AlarmaDeSensor alarma[CANTIDAD_SAL_ALARMA];

    
const struct getter * gettersAMostrar[]={
  &sensor[0],
  &sensor[1],
  &sensor[2],
  &sensor[3]
};					
const struct BlockConstBoxPriNC CBox_Pri={
      BoxPriNC,							/* funcion que procesa al box*/
      gettersAMostrar,      
      NULL						
};

NEW_FLASH_BKP_EN_FLASH(flash,0x4200); 


void SD_on1ms(void * sd){
    IncTimers(1); //Contador Estandard

    if(PromBkp_listoParaGrabarOBorrar(&flash) && getState()==AD_WAITING)
      TI1_SetPeriodMode(TI1_Pm_40ms);
    
    DpyAndSwitch();
}

void SD_on40ms(void * sd){
    (void)TI1_SetPeriodMode(TI1_Pm_1ms); //Next interrupt is 1ms length

    PromBkp_grabarOBorrar(&flash);

    IncTimers(TIEMPO_GRABACION); //Contador Estandard
}


void main (void){
 static  byte i;
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/
  

  Teclas_Init();
  Display_Init(); // Inicializacion del display
  com_Init(); 

  add1msListener(SD_on1ms,NULL);  //agregar a la interrupcion del timer cuando dura 1ms
  add40msListener(SD_on40ms,NULL);//agregar a la interrupcion del timer cuando dura 40ms
  
  for(i=0;i<CANTIDAD_CANALES;i++){
    newAllocObj(&AD1[i],TAdc,i);
    newAllocObj(&sensor[i],TSensor_TermoPT,&AD1[i],&sensor_config[i],"Sen");
  }
  for(i=0;i<CANTIDAD_SAL_ALARMA;i++)
    newAllocObj(&pwm[i],PWM,&pwm_config[i],i);
    
  for(i=0;i<CANTIDAD_SAL_ALARMA;i++)
    newAllocObj(&alarma[i],AlarmaDeSensor,&alar_conf[i],&sensor[i],&pwm[i],AL_TIME_DISCONECT);
  
 // newAllocObj(&msj1,MessageOut); 
  
  
 // PID_AddOnTSalChange(&pid,OnTSalChange,NULL);
  
  DN_InitSized(&CBox_Pri,5);
  Sets_Init2(4);
  DN_addBoxList(0,"tun ",(CANTIDAD_SAL_ALARMA+1));
  DN_addBoxList(0,"CAL ",(CANTIDAD_CANALES+1));
  DN_addBoxList(0,"Set ",1+(CANTIDAD_SAL_ALARMA+1)); 

  for(i=0;i<CANTIDAD_CANALES;i++)
    SnsHmi_Add(&sensor[i],i+1);
  for(i=0;i<CANTIDAD_SAL_ALARMA;i++)
    AlarmaDeSensorHmi_AddBoxes(&alarma[i],i+1);  
  Sets_AddBoxes();

  ModBusHmi_AddBoxes();

 for(i=0;i<CANTIDAD_CANALES;i++){  
 	  SnsHmi_ComuAdd(&sensor[i],1100+20*i);
 	}
 	
  

  for(i=0;i<CANTIDAD_SAL_ALARMA;i++){      
    PwmHmi_ComuAdd(&pwm[i],1000+10*i);	
  }
  for(i=0;i<CANTIDAD_SAL_ALARMA;i++){      
    AlarmaDeSensorHmi_ComuAdd(&alarma[i],1200+10*i);	
  }
  
 	ModBusHmi_ComuAdd(1300);

														 
  for(;;){
    static char tecla;
    tecla=get_key();
    WDog1_Clear();
      
    //Eventos
    for(i=0;i<CANTIDAD_CANALES;i++)
      SenTPT_Handler(&sensor[i]);
    
    DN_Proc(tecla);
    com_Handler();
    
    for(i=0;i<CANTIDAD_SAL_ALARMA;i++)
      AlarmaDeSensor_Handler(&alarma[i],tecla);
  }
}



