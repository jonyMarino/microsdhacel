#ifndef _CONFIGURACION_ALARMAS_HPP
#define _CONFIGURACION_ALARMAS_HPP

#include "AlarmaControl.hpp"
#include "Memoria/ManejadorMemoria.hpp"

class ConfiguracionAlarmas: public ConfiguracionAlarmaControl{
      public:
      
        typedef struct {
           TipoAdaptadorSalida tipoAdapSal;
           TipoControl tipoCrl;
          }AlarmConf;
      
         ConfiguracionAlarmas( AlarmConf &_conf_, struct ManejadorMemoria & _manejadorMemoria);
         TipoAdaptadorSalida getAdaptadorSalida();
         void setAdaptadorSalida(TipoAdaptadorSalida);
         TipoControl getTipoControl();
         void setTipoControl(TipoControl); 
       
       private:
       
          ManejadorMemoria &manejadorMemoria;

          AlarmConf &configuracion;  
    };    




#endif