#ifndef _CONFIGURACION_CONTROL_PID_HPP
#define _CONFIGURACION_CONTROL_PID_HPP


#include "ControlPID.hpp"
#include "Memoria/ManejadorMemoria.hpp"

class ConfiguracionControlPID: public ConfiguracionControl{
      public:
      
        typedef struct {
          int iSP;
          int iLimInfSP;
          int iLimSupSP;
          int iReset;
          int iHisteresis;
          fbyte eTipoControl;
          fbyte eSalidaControl;
          int iIntegral;
          int iDerivada;
          int iPotenciaInf;
          int iPotenciaSup;
          int iPotenciaManual;
          }ControlConf;
      
         ConfiguracionControlPID( ControlConf &_conf_, struct ManejadorMemoria & _manejadorMemoria);
         int getSetPoint();
         void setSetPoint(int);
         int getLimiteInferiorSetPoint();
         void setLimiteInferiorSetPoint(int val);
         int getLimiteSuperiorSetPoint();
         void setLimiteSuperiorSetPoint(int val);
         int getReset();
         void setReset(int val);
         int  getTipoControl();
         void setTipoControl(int val);
         int getTipoSalida();
         void setTipoSalida(int val);
         int getHisteresis();
         void setHisteresis(int val);
         int getIntegral();
         void setIntegral(int val);
         int getDerivada();
         void setDerivada(int val);
         int getLimiteInferiorPotencia();
         void setLimiteInferiorPotencia(int val);
         int getLimiteSuperiorPotencia();
         void setLimiteSuperiorPotencia(int val);
         int getPotenciaManual();
         void setPotenciaManual(int val);
          
       
       private:
       
          ManejadorMemoria &manejadorMemoria;

          ControlConf &configuracion;  
    };    




#endif