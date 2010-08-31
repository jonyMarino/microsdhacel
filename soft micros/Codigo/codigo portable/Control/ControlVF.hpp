#ifndef _CONTROL_VF_HPP
#define _CONTROL_VF_HPP

#include "ControlPID.hpp"
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
    
#define Te_MES_ANT(self) \
  self->getTempDeEtapa((self->getNroDeEtapa())-1) \
  
#define Ve_RMP(self) \
  self->getVelDeEtapa((self->getNroDeEtapa())) \
  
#define Ti_MES(self) \
  self->getTiempoDeEtapa((self->getNroDeEtapa())) \

#define SET_SP(self,val) \
  (self->getControlVF())->setSetPointEnRam(val) \

    
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
    virtual unsigned char getCantidadDeEtapas()=0;
    virtual void setCantidadDeEtapas(unsigned char val)=0;
    virtual unsigned char getVelDeEtapa(unsigned char nroEtp)=0;
    virtual void setVelDeEtapa(unsigned char nroEtp,unsigned char val)=0;
    virtual unsigned char getTempDeEtapa(unsigned char nroEtp)=0;
    virtual void setTempDeEtapa(unsigned char nroEtp,unsigned char val)=0;
    virtual unsigned char getTiempoDeEtapa(unsigned char nroEtp)=0;
    virtual void setTiempoDeEtapa(unsigned char nroEtp,unsigned char val)=0;
    friend class ControlVF;
};    

 

class ControlVF{
  public:
    
    ControlVF(Sensor& sensor,ControlPID& control,const ConfiguracionControlVF & configuracion);
   
    
    EstadoVF getEstadoVF();
    
    void setEstadoVF(EstadoVF state);
    
    ModoVF getModoVF();
    
    void setModoVF(ModoVF mod);
    
    unsigned char getNroDeEtapa();
     
    void setNroDeEtapa(unsigned char val); 
    
    void setSetPointVF(int val);
    
    const ConfiguracionControlVF* getConfiguracionVF();
    
    ControlPID * getControlVF();
    
    unsigned char getCantidadDeEtapas();
         
    void setCantidadDeEtapas(unsigned char val);
         
    unsigned char getVelDeEtapa(unsigned char nroEtp);
    
    void setVelDeEtapa(unsigned char nroEtp,unsigned char val);
    
    unsigned char getTempDeEtapa(unsigned char nroEtp);
    
    void setTempDeEtapa(unsigned char nroEtp,unsigned char val);
   
    unsigned char getTiempoDeEtapa(unsigned char nroEtp);
   
    void setTiempoDeEtapa(unsigned char nroEtp,unsigned char val);
   
    inline MessagesOut::Message getMensajeVF(){
      return  msj_VF;
    };
    inline void setMensajeVF(MessagesOut::Message mensj){
        msj_VF=mensj;
    };
    
    int getValMedido();
     
    word getMinutos();
    
    void setMinutos(word val); 
     
  private:
    
    ControlPID &_control;
    Sensor& _sensor;
    const ConfiguracionControlVF & _configuracion;
    EstadoVF estado;
    ModoVF modo;
    word minutos;
    unsigned char nroDeEtapaActual;
    RlxMTimer * timerVF;
    struct Method mOnTimeVF;
    MessagesOut * msjOutVF;
    MessagesOut::Message msj_VF;
    char mensaje[25];
};

#endif