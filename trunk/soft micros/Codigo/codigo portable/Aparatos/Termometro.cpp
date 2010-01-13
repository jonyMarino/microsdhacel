#include "WDog1.h"
#include "Termometro.hpp"
#include "Sensores.h"
#include "PromBkp.h"
#include "TI1.h"
#include "ModBusHmi.h"
#include "com_events.h"
#include "timer_interrupt.h"
#include "SnsHmi.h"
#include "display_teclas.h"
#include "teclas.h"
#include "SensorTermoPT100.hpp"

#pragma CONST_SEG PARAMETERS_PAGE
 
  const SensorTermoPT100::TConfSensor sensor_config[CANTIDAD_CANALES]= {
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

    if(PromBkp_listoParaGrabarOBorrar(&(_t->flash)) && Adc::getState()==IAdc::AD_WAITING)
      TI1_SetPeriodMode(TI1_Pm_40ms);
    
    DpyAndSwitch();
}

void Termometro::fOn40ms(void * termometro){
    struct Termometro * _t= (Termometro *)termometro;
    (void)TI1_SetPeriodMode(TI1_Pm_1ms); //Next interrupt is 1ms length

    PromBkp_grabarOBorrar(&(_t->flash));

}


Termometro::Termometro(struct ManejadorMemoria &_flash):flash(_flash),
#if CANTIDAD_CANALES == 1 
  ad0(0),
  sensor0(ad0,sensor_config[0],_flash){
#else
  ad0(0),
  ad1(1),
  sensor0(ad0,sensor_config[0],_flash),
  sensor1(ad1,sensor_config[1],_flash)
  {
#endif  
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  //PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/ 
  Teclas_Init();
  Display_Init(); // Inicializacion del display
  
  //this->flash=flash;
  
  newAlloced(&on1ms,&Method,fOn1ms,this);
  newAlloced(&on40ms,&Method,fOn40ms,this);

  add1msListener(&on1ms);  //agregar a la interrupcion del timer cuando dura 1ms
  add40msListener(&on40ms);//agregar a la interrupcion del timer cuando dura 40ms

	
}


void Termometro::mainLoop(void){
  byte i;
  
  WDog1_Clear();
  
  //for(i=0;i<CANTIDAD_CANALES;i++)
   #if CANTIDAD_CANALES == 1 
    sensor0.checkADC();
   #else
    sensor0.checkADC();
    sensor1.checkADC();
   #endif 
  
  PlataformaEmbedded::mainLoop();
}
