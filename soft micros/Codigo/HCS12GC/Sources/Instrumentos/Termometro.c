#include "WDog1.h"
#include "Termometro.h"
#include "PromBkp.h"
#include "TI1.h"
#include "ModBusHmi.h"
#include "com_events.h"
#include "timer_interrupt.h"
#include "SnsHmi.h"
#include "display_teclas.h"
#include "teclas.h"

void Termometro_defCtor(void * self,va_list * args);


const struct PlataformaEmbeddedClass Termometro={
  CLASS_INITIALIZATION(Class,Termometro,PlataformaEmbedded,Termometro_defCtor,Object_dtor,Object_differ,Object_puto),
  Termometro_mainLoop
};

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


void Termometro_on1ms(void * termometro){
    struct Termometro * _t= (struct Termometro *)termometro;

    if(PromBkp_listoParaGrabarOBorrar(_t->flash) && getState()==AD_WAITING)
      TI1_SetPeriodMode(TI1_Pm_40ms);
    
    DpyAndSwitch();
}

void Termometro_on40ms(void * termometro){
    struct Termometro * _t= (struct Termometro *)termometro;
    (void)TI1_SetPeriodMode(TI1_Pm_1ms); //Next interrupt is 1ms length

    PromBkp_grabarOBorrar(_t->flash);

}


void Termometro_constructor(void * self,struct ManejadorMemoria * flash){
 struct Termometro * _t= (struct Termometro *)self; 
 byte i;
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/ 
  Teclas_Init();
  Display_Init(); // Inicializacion del display
  
  _t->flash=flash;
  
  newAlloced(&_t->on1ms,&Method,Termometro_on1ms,self);
  newAlloced(&_t->on40ms,&Method,Termometro_on40ms,self);

  add1msListener(&_t->on1ms);  //agregar a la interrupcion del timer cuando dura 1ms
  add40msListener(&_t->on40ms);//agregar a la interrupcion del timer cuando dura 40ms

  for(i=0;i<CANTIDAD_CANALES;i++){    
    newAlloced(&(_t->AD1[i]),&Adc,i);
    newAlloced(&(_t->sensor[i]),&TSensor_TermoPT,&(_t->AD1[i]),&sensor_config[i],"Sen");
  }
	
}


void Termometro_defCtor(void * self,va_list * args){
  Termometro_constructor(self,va_arg(*args,struct ManejadorMemoria *));  
}


void Termometro_mainLoop(void * self){
  struct Termometro * _t= (struct Termometro *)self;
  byte i;
  WDog1_Clear();
  
  //Eventos   cambiar
  for(i=0;i<CANTIDAD_CANALES;i++)
    SenTPT_Handler(&_t->sensor[i]);
  
  //com_Handler();
  
  super_mainLoop(&Termometro,self);
}
