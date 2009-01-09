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
#include "bits2ULN.h"
#include "bits5ULN.h"
#include "Display1.h"
#include "Display2.h"
#include "matriz.h"

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
DECLARACION_CONF_CONTROL;
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

    
const struct BlockConstBoxPri1c CBox_Pri={
      BoxPri1c,							/* funcion que procesa al box*/
      &sensor[0],
      NULL						
};

static const byte  DigInfOn[DIGITOS]={0x10,0x20,0x40,0x80};		// señales de control del display
static const byte  DigSupOn[DIGITOS]={0x01,0x02,0x04,0x08};

void main (void){

  char tecla; 
  bool prevVal;
  byte i=0;
  
  struct Timer * timer = newObj(Timer,(ulong)2000);
  
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/
 
  Teclas_Init();
  Display_Init(); // Inicializacion del display

 // com_Init(); 

 // bits2ULN_PutVal(0);		//PTJ
 // bits5ULN_PutVal(0x1); //PTM
  Display1_PutVal(Car_Ini['h'-'-']);  //PTA
  Display2_PutVal(Car_Ini['h'-'-']);  //PTA
								 
  for(;;){
    if(timer && Timer_isfinish(timer)){
      if (i==8){
        
        deleteObj(&timer);
        break;
      }
      Timer_Restart(timer);
      
      if(i<2)					// PTM
      {  
        bits2ULN_PutVal(0);		//PTJ
        bits5ULN_PutVal(DigInfOn[i]); //PTM
      }  
      else if (i<4)
      {
        bits5ULN_PutVal(0);
        bits2ULN_PutVal(DigInfOn[i]);		// PTJ        
      }
      else{
        bits2ULN_PutVal(0);		// PTJ 
        bits5ULN_PutVal(DigSupOn[i-4]); //PTM  
      }
      i++;
    }
    WDog1_Clear();
  }
  
  PasarASCII("biEnVEnido",0);
  PasarASCII("Soy ",1);
  PasarASCII("Jony",2);
  PasarASCII("MArino",3);
  for(;;){
    DpyAndSwitch();
    WDog1_Clear();  
  }
}

