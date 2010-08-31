#ifndef _CONFIGURACION_VF_HPP
#define _CONFIGURACION_VF_HPP


#include "ControlVF.hpp"
#include "Memoria/ManejadorMemoria.hpp"

class ConfiguracionVF: public ConfiguracionControlVF{
      public:
        typedef struct{
          unsigned char velocidad;
          unsigned char temperatura;
          unsigned char tiempo;
        }Etapa;
        
        typedef struct {
          unsigned char iCantDeEtapas;
          Etapa iEtapa[10];
          
          }ConfVF;
      
         ConfiguracionVF( ConfVF &_conf_, struct ManejadorMemoria & _manejadorMemoria);
         unsigned char getCantidadDeEtapas();
         void setCantidadDeEtapas(unsigned char val);
         unsigned char getVelDeEtapa(unsigned char nroEtp);
         void setVelDeEtapa(unsigned char nroEtp,unsigned char val);
         unsigned char getTempDeEtapa(unsigned char nroEtp);
         void setTempDeEtapa(unsigned char nroEtp,unsigned char val);
         unsigned char getTiempoDeEtapa(unsigned char nroEtp);
         void setTiempoDeEtapa(unsigned char nroEtp,unsigned char val);
   
       private:
       
          ManejadorMemoria &manejadorMemoria;

          ConfVF &configuracion;  
    };    




#endif