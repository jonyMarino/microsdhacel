#ifndef _CONFIGURACION_RETRANSMISION_HPP
#define _CONFIGURACION_RETRANSMISION_HPP

#include "Retransmision.hpp"
#include "Memoria/ManejadorMemoria.hpp"

class ConfiguracionRetransm: public ConfiguracionRetransmision{
      public:
      
        typedef struct {
           int retLow;
           int retHi;
          }RetConf;
      
         ConfiguracionRetransm( RetConf &_conf_, struct ManejadorMemoria & _manejadorMemoria);
         int getLimiteInferior();
         int getLimiteSuperior();
         void setLimiteInferior(int);
         void setLimiteSuperior(int); 
       
       private:
       
          ManejadorMemoria &manejadorMemoria;

          RetConf &configuracion;  
    };    




#endif