#ifndef _TERMOMETRO_HPP
#define _TERMOMETRO_HPP

#include "Object.h"
#include "Mydefines.h"
#include "ClassADC.h"
#include "SensorTPT_Class.h"
#include "ManejadorMemoria.h"
#include "PlataformaEmbedded.hpp"
#include "Method.h"

class Termometro: public PlataformaEmbedded{
  public:
    Termometro(struct ManejadorMemoria * flash);
    struct TSensor_TermoPT sensor;//[CANTIDAD_CANALES];
    struct Adc  AD1[CANTIDAD_CANALES];
    virtual void mainLoop(void);
  protected:
    struct ManejadorMemoria * flash; 
    struct Method on1ms;
    struct Method on40ms;
  private:
    static void fOn1ms(void * termometro);
    static void fOn40ms(void * termometro);      
};

#endif 