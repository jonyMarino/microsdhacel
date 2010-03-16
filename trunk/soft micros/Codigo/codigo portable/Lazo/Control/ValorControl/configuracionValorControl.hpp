#ifndef _CONFIGURACION_VALOR_CONTROL_HPP
#define _CONFIGURACION_VALOR_CONTROL_HPP

#include "ValorControl.hpp"
#include "Memoria/ManejadorMemoria.hpp"

class ConfiguracionValorControlado: public ConfiguracionValorControl{
      public:
      
        typedef struct {
           int valAControlar;
          }ValorControlConf;
      
         ConfiguracionValorControlado( ValorControlConf &_conf_, struct ManejadorMemoria & _manejadorMemoria);
         int getValorControlador();
         void setValorControlador(int);
         
       private:
       
          ManejadorMemoria &manejadorMemoria;

          ValorControlConf &_configuracion;  
    };    




#endif