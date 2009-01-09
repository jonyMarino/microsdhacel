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
#include "FlashBkpEnFlash.h"
#include "TI1.h"
#include "timer_interrupt.h"
#include "RlxMTimer.h"


#pragma CONST_SEG PARAMETERS_PAGE
volatile const SensorRpmConf config=DEFAULT_SENSOR_RPM_CONF;
volatile const TConfPWM pwm_config={
  9
};
volatile const ControlConf pid_config=ControlDefaultConf; 
#pragma CONST_SEG DEFAULT
struct Timer * timer;
struct PWMTimer  pwm;
struct ControlPID pid; 
struct MessageOut msj1;
struct Capturador * cap;
struct ThreadAdjuntable mainThread;
struct SensorRpm sensorRpm;

  
const struct BlockConstBoxPri1c CBox_Pri={
      &BoxPri1c,							/* funcion que procesa al box*/
      &sensorRpm,
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

//#define _ENTRADA_SIMULADA

#ifdef _ENTRADA_SIMULADA
  #define GET_INSTANCE() CapturadorSimulado_getInstancia()
#else
  #define GET_INSTANCE() CapturadorPT2_getInstancia()
#endif

#define CNTR_TIME_DISCONECT	 2000



NEW_FLASH_BKP_EN_FLASH(flash,0x4400);

void on1ms(void * termometro){
   
    if(PromBkp_listoParaGrabarOBorrar(&flash))
      TI1_SetPeriodMode(TI1_Pm_40ms);
    
    DpyAndSwitch();
}

void on40ms(void * termometro){
    (void)TI1_SetPeriodMode(TI1_Pm_1ms); //Next interrupt is 1ms length

    PromBkp_grabarOBorrar(&flash);

   
}

void main (void){
  char tecla;
  timer= new(&Timer,(ulong)500);
   
  
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/
  
  Teclas_Init();
  Display_Init(); // Inicializacion del display
  
  add1msListener(on1ms,0);
  add40msListener(on40ms,0);
  
  newAlloced(&mainThread,&ThreadAdjuntable);
  cap=GET_INSTANCE();
  #ifdef _ENTRADA_SIMULADA
  CapturadorSimulado_setMicroSegundos(cap,100000000);
  CapturadorSimulado_setPulsos(cap,2);
  #endif
  {
    void * adjuntador= ThreadAdjuntable_getAdjuntador(&mainThread);
    newAlloced(&sensorRpm,&SensorRpm,adjuntador,1000,cap,&config,"SEn rPM");
    delete(adjuntador);
  }
  newAlloced(&pwm,&PWMTimer,&pwm_config,0);
  newAlloced(&pid,ControlPID,&pid_config,&sensorRpm,&pwm,CNTR_TIME_DISCONECT);
  newAlloced(&msj1,MessageOut); 
  
  
  PID_AddOnTSalChange(&pid,OnTSalChange,NULL);
  
  DN_Init(&CBox_Pri);
  Sets_Init();
  PWM_Hmi_Add(&pwm,0);
  SenRpmHmi_Add(&sensorRpm,0);
  PidHmi_AddBoxes(&pid,0);
//  PidHmi_AddBoxes(&pid,2);
//  PidHmi_AddBoxes(&pid,3);
  Sets_AddBoxes();

 	
 	  														 
  for(;;){
    WDog1_Clear();
    tecla=get_key();  
    
  /*  
    if(Timer_isfinish(timer)){
      Timer_Restart(timer);
      _GetterPrint(&sensorRpm,0);
     // CapturadorSimulado_setPulsos(cap,CapturadorSimulado_getPulsos(cap)+1);
    }
		*/
    //Eventos
    MethodContainer_execute(&mainThread);
    
   
    
    DN_Proc(tecla);
  }
}