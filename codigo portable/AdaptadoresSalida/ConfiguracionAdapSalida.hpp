#ifndef _CONFIGURACION_ADAP_SALIDA_HPP
#define _CONFIGURACION_ADAP_SALIDA_HPP

#include "AdaptadorSalidaConfiguracion.hpp"
#include "Memoria/ManejadorMemoria.hpp"

class ConfiguracionAdapSalida: public AdaptadorSalidaConfiguracion{
      public:
      
        typedef struct {
           int histeresis; 
           TipoSalida tipoSalida;
          }AdapSalConf;
      
         ConfiguracionAdapSalida( AdapSalConf &_conf_, struct ManejadorMemoria & _manejadorMemoria);
         int getHisteresis();
         TipoSalida getTipoSalida();
         void setHisteresis(int);
         void setTipoSalida(TipoSalida); 
       
       private:
       
          ManejadorMemoria &manejadorMemoria;

          AdapSalConf &configuracion;  
    };    




#endif