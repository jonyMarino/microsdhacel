#include "Timer.h"
#include "display.h"
#include "WDog1.h"
#include "teclas.h"
#include "Class.h"
#include "ADC.h"
#include "ClassADC.h"
#include "Grabacion.h"
#include "Sensores.h"
#include "SensorTPT_Class.h"

#pragma CONST_SEG PARAMETERS_PAGE
volatile const SensorConf config[CANTIDAD_CANALES];
#pragma CONST_SEG DEFAULT
struct Timer * timer;
struct TAdc * AD1;
struct TSensor_TermoPT * sensor;

void main (void){
  timer= newObj(Timer,(ulong)500); 
  
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/
  AD1 = newObj(TAdc,0);
  sensor = newObj(TSensor_TermoPT,AD1,&config[0]);
  
  Teclas_Init();
  Display_Init(); // Inicializacion del display
  
  set_Sensor(sensor,SENSOR_JB);
  set_ganancia(sensor,1000);
 															 
  for(;;){
    WDog1_Clear();

      if(Sensor_isnew(sensor)){
        _Getter_getVal(sensor);
/*        Pasar_Numero(Sensor_getVal(sensor),0,SENSOR_Decimales(get_Sensor(sensor)));
        if(SenTPT_getState(sensor)==SENSOR_OF)
          PasarASCII("OF  ",0);
        else if(SenTPT_getState(sensor)==SENSOR_UF)
          PasarASCII("UF  ",0); 
        else
*/				Pasar_Numero(ADC_getTA(),1,0);
          Pasar_Numero(ADC_getADTA(),0,0);
      }
      
      //Eventos
      SenTPT_Handler(sensor);
  }
}