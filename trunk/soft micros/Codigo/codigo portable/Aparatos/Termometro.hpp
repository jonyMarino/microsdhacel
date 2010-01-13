#ifndef _TERMOMETRO_HPP
#define _TERMOMETRO_HPP

#include "Object.h"
//#include "Mydefines.h"
//#include "ClassADC.h"
#include "Adc.hpp"
#include "IAdc.hpp"
#include "SensorTermoPT100.hpp"
//#include "SensorTPT_Class.h"
#include "ManejadorMemoria.h"
#include "PlataformaEmbedded.hpp"
#include "Method.h"

#define CANTIDAD_CANALES  1
//extern const SensorTermoPT100::TConfSensor sensor_config[CANTIDAD_CANALES];

class Termometro: public PlataformaEmbedded{
  public:
    Termometro(struct ManejadorMemoria & flash/*,SensorTermoPT100 _sensor[]*/);
   // struct TSensor_TermoPT sensor;//[CANTIDAD_CANALES];
   #if CANTIDAD_CANALES == 1     
    Adc  ad0;
    SensorTermoPT100 sensor0;
   #else
    Adc  ad0;
    Adc  ad1;
    SensorTermoPT100 sensor0;
    SensorTermoPT100 sensor1;
   #endif 
    
    virtual void mainLoop(void);
  protected:
    struct ManejadorMemoria &flash; 
    struct Method on1ms;
    struct Method on40ms;
  private:
    static void fOn1ms(void * termometro);
    static void fOn40ms(void * termometro);      
};

#endif 