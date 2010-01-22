#include "WDog1.h"
#include "Termometro.hpp"
#include "Sensores.h"
#include "TI1.h"
#include "ModBusHmi.h"
#include "com_events.h"
#include "timer_interrupt.h"
#include "SnsHmi.h"
#include "teclas.h"
#include "SensorTermoPT100.hpp"


void fOn1ms(void * _self){
    struct Termometro * self= (Termometro *)_self;

    if( (self->flash).listoParaGrabarOBorrar() && Adc::getState()==IAdc::AD_WAITING)
      TI1_SetPeriodMode(TI1_Pm_40ms);
}

void fOn40ms(void * _self){
    struct Termometro * self= (Termometro *)_self;
    (void)TI1_SetPeriodMode(TI1_Pm_1ms); //Next interrupt is 1ms length

    self->flash.grabarOBorrar();

}

Termometro::Termometro(struct PromBkp &_flash):on1ms(fOn1ms,this),on40ms(fOn40ms,this),flash(_flash){
  add1msListener(&on1ms);  //agregar a la interrupcion del timer cuando dura 1ms
  add40msListener(&on40ms);//agregar a la interrupcion del timer cuando dura 40ms
}


void Termometro::mainLoop(void){
  PlataformaEmbedded::mainLoop();
}
