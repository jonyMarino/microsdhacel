#ifndef _CONFIGURACION_LAZO_ALARMAS_HPP
#define _CONFIGURACION_LAZO_ALARMAS_HPP

#include "CoordinadorLazosAlCntrRet.hpp"
#include "Memoria/ManejadorMemoria.hpp"

class ConfiguracionLazoAlarmas: public ConfiguracionCoordinadorLazosAlCntrRet{
      public:
      
        typedef struct {
           TipoLazo tipoLazo;
          }LazoAlarmConf;
      
         ConfiguracionLazoAlarmas( LazoAlarmConf &_conf_, struct ManejadorMemoria & _manejadorMemoria);
         TipoLazo getLazo();
         void setLazo(TipoLazo);
       
       private:
       
          ManejadorMemoria &manejadorMemoria;

          LazoAlarmConf &configuracion;  
    };    




#endif