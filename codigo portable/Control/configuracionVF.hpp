#ifndef _CONFIGURACION_VF_HPP
#define _CONFIGURACION_VF_HPP


#include "ControlVF.hpp"
#include "Memoria/ManejadorMemoria.hpp"

class ConfiguracionVF: public ConfiguracionControlVF{
      public:
        typedef struct{
          int velocidad;
          int temperatura;
          int tiempo;
        }Etapa;
        
        typedef struct {
          int iCantDeEtapas;
          Etapa iEtapa[10];
          
          }ConfVF;
      
         ConfiguracionVF( ConfVF &_conf_, struct ManejadorMemoria & _manejadorMemoria);
         int getCantidadDeEtapas();
         void setCantidadDeEtapas(int val);
         int getVelDeEtapa(int nroEtp);
         void setVelDeEtapa(int nroEtp,int val);
         int getTempDeEtapa(int nroEtp);
         void setTempDeEtapa(int nroEtp,int val);
         int getTiempoDeEtapa(int nroEtp);
         void setTiempoDeEtapa(int nroEtp,int val);
   
       private:
       
          ManejadorMemoria &manejadorMemoria;

          ConfVF &configuracion;  
    };    




#endif