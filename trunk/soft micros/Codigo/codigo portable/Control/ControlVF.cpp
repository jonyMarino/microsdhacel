#include <stdarg.h>
#include <stddef.h>		
#include <stdlib.h>
#include "ControlVF.hpp"

void procesarVF(void * a);

ControlVF::ControlVF(Sensor& sensor,ControlPID& control,const ConfiguracionControlVF & configuracion):_sensor(sensor),_control(control),_configuracion(configuracion){
 
  mOnTimeVF.pmethod=&procesarVF;
  mOnTimeVF.obj=this;
  
  timerVF = new RlxMTimer(TIEMPO_VF,mOnTimeVF);
  
}


EstadoVF ControlVF::getEstadoVF(){
 return estado;
}

void ControlVF::setEstadoVF(EstadoVF state){
   estado=state;
}

ModoVF ControlVF::getModoVF(){
  return modo;
}
    
void ControlVF::setModoVF(ModoVF mod){
    modo=mod;
    setNroDeEtapa(1);
    
}

unsigned char ControlVF::getNroDeEtapa(){
  return nroDeEtapaActual;
}

void ControlVF::setNroDeEtapa(unsigned char val){
  nroDeEtapaActual=val;
}

void ControlVF::setSetPointVF(int val){
  _control.setSetPointEnRam(val);
}

const ConfiguracionControlVF* ControlVF::getConfiguracionVF(){
  return &_configuracion;
}

ControlPID * ControlVF::getControlVF(){
  return &_control;
}

unsigned char ControlVF::getCantidadDeEtapas(){
  return _configuracion.getCantidadDeEtapas();
}

void ControlVF::setCantidadDeEtapas(unsigned char val){
    _configuracion.setCantidadDeEtapas(val);
}

unsigned char ControlVF::getVelDeEtapa(unsigned char nroEtp){
  return _configuracion.getVelDeEtapa(nroEtp);
}

void ControlVF::setVelDeEtapa(unsigned char nroEtp,unsigned char val){
  _configuracion.setVelDeEtapa(nroEtp,val);
}

unsigned char ControlVF::getTempDeEtapa(unsigned char nroEtp){
  return _configuracion.getTempDeEtapa(nroEtp);
}

void ControlVF::setTempDeEtapa(unsigned char nroEtp,unsigned char val){
    _configuracion.setTempDeEtapa(nroEtp,val);
}

unsigned char ControlVF::getTiempoDeEtapa(unsigned char nroEtp){
  return _configuracion.getTiempoDeEtapa(nroEtp);
}

void ControlVF::setTiempoDeEtapa(unsigned char nroEtp,unsigned char val){
   _configuracion.setTiempoDeEtapa(nroEtp,val);
}


int ControlVF::getValMedido(){
  return _sensor.getVal();
}


word ControlVF::getMinutos(){
  return minutos;
}
    
void ControlVF::setMinutos(word val){
  minutos=val;
}


void procesarVF(void * a){
 char Kdec;
 long tempActVF;
 static char contProtecRuido=0;
 static dword rampa_mestaTime=0;
 ControlVF * self=(ControlVF*)a; 
 
  if(self->getModoVF() == RUN){   //estoy corriendo?
    
   rampa_mestaTime++;

/* calculo de la temperatura de la rampa cada 1 segundos y             */
/* calculo del tiempo transcurrido una ves llegado a la temp de meseta */  
                              
     
 /*/////////////////calculo del setpoint(tmpAct)/////////////// */
  
   if(self->getEstadoVF() == RAMPA) {                                                     //si, es rampa?
    
      if(((self->getControlVF())->getDecimales()) == 0)                                             //si, pongo decimales
        Kdec = 10;
      else
        Kdec = 1;
      
       
       if(Te_MES(self) > Te_MES_ANT(self)){                                           //pendiente positiva? 
          tempActVF = Te_MES_ANT(self) + (dword)(Ve_RMP(self)*rampa_mestaTime)/(unsigned int)(60 * Kdec * Unidad);    //si, calculo sp
          
 /*///////////////control de fin de rampa//////////////////////// */
       if(self->getValMedido()>=(Te_MES(self))){                                           //verifico la condicion contProtecRuido veces
           contProtecRuido++;
           
           if(contProtecRuido==PROTEC)
              contProtecRuido=0;
            else{
              SET_SP(self,tempActVF);
              return;
            }
            tempActVF = Te_MES(self); 
            rampa_mestaTime=0;
            self->setEstadoVF(MESETA);
            SET_SP(self,tempActVF);                                                     //comienzo de meseta
            return;
        }
          
        //verifico la condicion para el limite max
        if(tempActVF>=(Te_MES(self)+MaxMin)){                                   //me pase?
          tempActVF=Te_MES(self)+MaxMin;                                           //limito
          SET_SP(self,tempActVF);
        }else
          return;         //retorno por que no llegue al limite max
        
       }
       
       if(Te_MES(self) < Te_MES_ANT(self)){                                               //pendiente negativa?
        tempActVF = Te_MES_ANT(self) - (dword)(Ve_RMP(self)*rampa_mestaTime)/(unsigned int)(60 * Kdec * Unidad);
        /*/////////control de fin de rampa/////////////////// */
        if(self->getValMedido()<=Te_MES(self)){
           contProtecRuido++;
           
           if(contProtecRuido==PROTEC)
              contProtecRuido=0;
            else{
              SET_SP(self,tempActVF);
              return;
            }
            tempActVF = Te_MES(self); 
            rampa_mestaTime=0;
            self->setEstadoVF(MESETA);                                                      //comienzo de meseta
            SET_SP(self,tempActVF);
            return;
        }
          
        //verifico la condicion para el limite min
        if(tempActVF<=(Te_MES(self)-MaxMin)) {
          tempActVF=Te_MES(self)-MaxMin;
          SET_SP(self,tempActVF);
        }else
          return;                                                             //retorno por que no llegue al limite max
        
       }
       
       if(Te_MES(self) == Te_MES_ANT(self)){                                               //iguales?
          tempActVF =Te_MES(self);
          rampa_mestaTime=0;
          contProtecRuido=0;
          self->setEstadoVF(MESETA);                                                     //comienzo de meseta
          SET_SP(self,tempActVF);
          return;     
       }
      
  }
   
/*/////////////control de fin de meseta//////////////////////////*/  
  
 else if((Ti_MES(self)*60) <= rampa_mestaTime){                                    //si no era rampa es meseta 
    rampa_mestaTime = 0;
    self->setMinutos(1);
    self->setNroDeEtapa((self->getNroDeEtapa())+1);
    if(((self->getNroDeEtapa())-1)<(self->getCantidadDeEtapas())){                                              //supere la cantidad de etapas?
      self->setEstadoVF(RAMPA);      //INICIA RAMPA
      return;
    }else {                                                                     // si supere -> fin
      tempActVF =Te_MES_ANT(self);
      SET_SP(self,tempActVF); 
      self->setModoVF(FIN);
      
    }
  }

 
}else{                                                                           //si no era run era stop  
  rampa_mestaTime = 0;                                                           // reseteo todo
  contProtecRuido=0;
  self->setEstadoVF(RAMPA);
  tempActVF=0;
  SET_SP(self,tempActVF);   
} 
}

