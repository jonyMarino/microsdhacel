#ifndef _TERMOMETRO_HPP
#define _TERMOMETRO_HPP

#include "Adc.hpp"
#include "IAdc.hpp"
#include "SensorTermoPT100.hpp"
#include "Memoria/Prom/PromBkp.hpp"
#include "PlataformaEmbedded.hpp"
#include "OOC/lang/reflect/lib_cpp/Method.hpp"


class Termometro: public PlataformaEmbedded{
  public:
    Termometro(PromBkp & flash);    
    virtual void mainLoop(void);
  protected:
    PromBkp &flash; 
    struct Method on1ms;
    struct Method on40ms;
  private:
    friend void fOn1ms(void * termometro);
    friend void fOn40ms(void * termometro);      
};

#endif 