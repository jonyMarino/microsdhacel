#ifndef _CONTROL_VF_HPP
#define _CONTROL_VF_HPP

#include "ControlPID.hpp"
#include "SensorTermoPT100.hpp"
#include "LazoControl.hpp"
#include "SalidaBanda.hpp"
#include "ValorControlProporcional.hpp"
#include "ValorControlRelativo.hpp"
#include "Timer/FlagTimer/FlagTimer.hpp"
#include "Timer/RlxMTimer/RlxMTimer.hpp"
#include "MethodContainer.hpp"
#include "MessagesOut.hpp"

#define TIEMPO_VF 1000

#define PROTEC     2 

#define MaxMin     10  

#ifdef GOROSITO
#define Unidad     60
#else
#define Unidad     1
#endif 

#define Te_MES(self) \
  self->getTempDeEtapa((self->getNroDeEtapa())) \
    
#define Ve_RMP(self) \
  self->getVelDeEtapa((self->getNroDeEtapa())) \
  
#define Ti_MES(self) \
  self->getTiempoDeEtapa((self->getNroDeEtapa())) \

#define SET_SP(self,val) \
  self->setSetPointVF(val) \

    
 typedef enum{
     RAMPA, 
     MESETA
    }EstadoVF;
	
 typedef enum{
     RUN, 
     FIN 
    }ModoVF;
      
class ConfiguracionControlVF{
  public:
    virtual int getCantidadDeEtapas()=0;
    virtual void setCantidadDeEtapas(int val)=0;
    virtual int getVelDeEtapa(int nroEtp)=0;
    virtual void setVelDeEtapa(int nroEtp,int val)=0;
    virtual int getTempDeEtapa(int nroEtp)=0;
    virtual void setTempDeEtapa(int nroEtp,int val)=0;
    virtual int getTiempoDeEtapa(int nroEtp)=0;
    virtual void setTiempoDeEtapa(int nroEtp,int val)=0;
    friend class ControlVF;
};    

 

class ControlVF{
  public:
    
    ControlVF(Sensor& sensor,SetPoint& setPoint,const ConfiguracionControlVF & configuracion,MessagesOut* msj);
   
    
    EstadoVF getEstadoVF();
    
    void setEstadoVF(EstadoVF state);
    
    ModoVF getModoVF();
    
    void setModoVF(ModoVF mod);
    
    int getNroDeEtapa();
     
    void setNroDeEtapa(int val); 
    
    void setSetPointVF(int val);
    
    int getSetPointVF();
    
    const ConfiguracionControlVF* getConfiguracionVF();
    
    int getCantidadDeEtapas();
         
    void setCantidadDeEtapas(int val);
         
    int getVelDeEtapa(int nroEtp);
    
    void setVelDeEtapa(int nroEtp,int val);
    
    int getTempDeEtapa(int nroEtp);
    
    void setTempDeEtapa(int nroEtp,int val);
   
    int getTiempoDeEtapa(int nroEtp);
   
    void setTiempoDeEtapa(int nroEtp,int val);
    
    void procesaTeclasVF(uchar tecla);
    
    void procesCartelesVF();
   
    inline MessagesOut::Message getMensajeVF(){
      return  msj_VF;
    };
    inline void setMensajeVF(MessagesOut::Message mensj){
        msj_VF=mensj;
    };
    
    int getValMedido();
     
    word getMinutos();
    
    void setMinutos(word val); 
    
    uchar getDecimales();
    
     
  private:
    
    SetPoint &_setPoint;
    Sensor& _sensor;
    const ConfiguracionControlVF & _configuracion;
    EstadoVF estado;
    ModoVF modo;
    word minutos;
    int nroDeEtapaActual;
    RlxMTimer * timerVF;
    struct Method mOnTimeVF;
    MessagesOut * msjOutVF;
    MessagesOut::Message msj_VF;
    char mensaje[25];
};

#endif