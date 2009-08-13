#include "WDog1.h"
#include "Termometro.hpp"
#include "PromBkp.h"
#include "TI1.h"
#include "ModBusHmi.h"
#include "com_events.h"
#include "timer_interrupt.h"
#include "SnsHmi.h"
#include "display_teclas.h"
#include "teclas.h"

#pragma CONST_SEG PARAMETERS_PAGE
 volatile const SensorConf sensor_config[CANTIDAD_CANALES]= {
    STPT_DEF_CONF,
  #if CANTIDAD_CANALES>1 
    STPT_DEF_CONF,
      #if CANTIDAD_CANALES>2
        STPT_DEF_CONF,
        #if CANTIDAD_CANALES>3
          STPT_DEF_CONF,
        #endif
      #endif
  #endif
 };
#pragma CONST_SEG DEFAULT


void Termometro::fOn1ms(void * termometro){
    struct Termometro * _t= (Termometro *)termometro;

    if(PromBkp_listoParaGrabarOBorrar(_t->flash) && getState()==AD_WAITING)
      TI1_SetPeriodMode(TI1_Pm_40ms);
    
    DpyAndSwitch();
}

void Termometro::fOn40ms(void * termometro){
    struct Termometro * _t= (Termometro *)termometro;
    (void)TI1_SetPeriodMode(TI1_Pm_1ms); //Next interrupt is 1ms length

    PromBkp_grabarOBorrar(_t->flash);

}


Termometro::Termometro(struct ManejadorMemoria * flash):sensor(){
 byte i;
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/ 
  Teclas_Init();
  Display_Init(); // Inicializacion del display
  
  this->flash=flash;
  
  newAlloced(&on1ms,&Method,fOn1ms,this);
  newAlloced(&on40ms,&Method,fOn40ms,this);

  add1msListener(&on1ms);  //agregar a la interrupcion del timer cuando dura 1ms
  add40msListener(&on40ms);//agregar a la interrupcion del timer cuando dura 40ms

  for(i=0;i<CANTIDAD_CANALES;i++){    
    newAlloced(&(AD1[i]),&Adc,i);
    newAlloced(&(sensor),&TSensor_TermoPT,&(AD1[i]),&sensor_config[i],"Sen");
  }
	
}


void Termometro::mainLoop(void){
  byte i;
  
  WDog1_Clear();
  
  for(i=0;i<CANTIDAD_CANALES;i++)
    SenTPT_Handler(&sensor);
  
  PlataformaEmbedded::mainLoop();
}
