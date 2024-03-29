#include <stdarg.h>
#include <stddef.h>		
#include <stdlib.h>
#include "ControlVF.hpp"

void procesarVF(void * a);

ControlVF::ControlVF(Sensor& sensor,SetPoint& setPoint,const ConfiguracionControlVF & configuracion,MessagesOut* msj):_sensor(sensor),_setPoint(setPoint),_configuracion(configuracion),msjOutVF(msj){
  estado=RAMPA;
  modo=FIN;
  nroDeEtapaActual=1;
  minutos=0;
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

int ControlVF::getNroDeEtapa(){
  return nroDeEtapaActual;
}

void ControlVF::setNroDeEtapa(int val){
  nroDeEtapaActual=val;
}

void ControlVF::setSetPointVF(int val){
  _setPoint.setVal(val);
}


int  ControlVF::getSetPointVF(){
  return  _setPoint.getVal();
}

const ConfiguracionControlVF* ControlVF::getConfiguracionVF(){
  return &_configuracion;
}

int ControlVF::getCantidadDeEtapas(){
  return _configuracion.getCantidadDeEtapas();
}

void ControlVF::setCantidadDeEtapas(int val){
    _configuracion.setCantidadDeEtapas(val);
}

int ControlVF::getVelDeEtapa(int nroEtp){
  return _configuracion.getVelDeEtapa(nroEtp);
}

void ControlVF::setVelDeEtapa(int nroEtp,int val){
  _configuracion.setVelDeEtapa(nroEtp,val);
}

int ControlVF::getTempDeEtapa(int nroEtp){
  return _configuracion.getTempDeEtapa(nroEtp);
}

void ControlVF::setTempDeEtapa(int nroEtp,int val){
    _configuracion.setTempDeEtapa(nroEtp,val);
}

int ControlVF::getTiempoDeEtapa(int nroEtp){
  return _configuracion.getTiempoDeEtapa(nroEtp);
}

void ControlVF::setTiempoDeEtapa(int nroEtp,int val){
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


void ControlVF::procesaTeclasVF(uchar tecla){
  if(tecla == 'u')
    setModoVF(RUN);
  if(tecla == 'd')
    if(nroDeEtapaActual<getCantidadDeEtapas()){
      nroDeEtapaActual++;
      setEstadoVF(RAMPA);
    }else
     setModoVF(FIN); 
    
}


void ControlVF::procesCartelesVF(){
      
      if(getModoVF()==RUN){
        
        if(getEstadoVF()==RAMPA){
          if(msj_VF){
              msjOutVF->deleteMessage(msj_VF);
              msj_VF = NULL;
            }
            
            #ifndef BKR
            mensaje[0]='r';
            mensaje[1]='A';
            mensaje[2]='m';
            mensaje[3]='P';
            mensaje[4]='A';  
            if(getNroDeEtapa()/10){
              mensaje[5]=(char)((getNroDeEtapa()/10)+0x30);
              mensaje[6]=(char)((getNroDeEtapa()%10)+0x30);
              mensaje[7]='\0';
            }else{
              mensaje[5]=(char)((getNroDeEtapa())+0x30);
              mensaje[6]='\0';
            }
            #else
            mensaje[0]='C';
            mensaje[1]='A';
            mensaje[2]='L';
            mensaje[3]='E';
            mensaje[4]='n';
            mensaje[5]='t';
            mensaje[6]='A';
            mensaje[7]='n';
            mensaje[8]='d';
            mensaje[9]='o';  
            mensaje[10]='\0';
            #endif
            if(!msj_VF)
              msj_VF = msjOutVF->addMessage(mensaje);
       
        }else if(getEstadoVF()==MESETA) {
        
            if(msj_VF){ 
              msjOutVF->deleteMessage(msj_VF);
               msj_VF = NULL; 
            }
            
            #ifndef BKR
            mensaje[0]='m';
            mensaje[1]='E';
            mensaje[2]='S';
            mensaje[3]='E';
            mensaje[4]='t';
            mensaje[5]='A';
            
            if(getNroDeEtapa()/10){
              mensaje[6]=(char)((getNroDeEtapa()/10)+0x30);
              mensaje[7]=(char)((getNroDeEtapa()%10)+0x30);
              
            }else{
              mensaje[6]=(char)((getNroDeEtapa())+0x30);
              mensaje[7]=' ';
            }
       
            if((minutos+1)/100){
              mensaje[8]=(minutos+1)/100+0x30;
              mensaje[9]=((minutos+1)%100)/10+0x30; 
              mensaje[10]=(minutos+1)%10+0x30;
              mensaje[11]='m';
              mensaje[12]='i';
              mensaje[13]='n';
              mensaje[14]='\0';
            }else if(((minutos+1)/10) && ((minutos+1)/100) != 1) {
              mensaje[8]=(minutos+1)/10+0x30; 
              mensaje[9]=(minutos+1)%10+0x30;
              mensaje[10]='m';
              mensaje[11]='i';
              mensaje[12]='n';
              mensaje[13]='\0';
            }else{
              mensaje[8]=(minutos+1+0x30);
              mensaje[9]='m';
              mensaje[10]='i';
              mensaje[11]='n';
              mensaje[12]='\0';
             
             #else
              
              mensaje[0]='F';
              mensaje[1]='i';
              mensaje[2]='n';
              mensaje[3]='A';
              mensaje[4]='L';
              mensaje[5]=' ';
              
              mensaje[6]='E';
              mensaje[7]='n';
              mensaje[8]=' ';
              
              if((getTiempoDeEtapa(getNroDeEtapa())-minutos)/100){
              mensaje[9]=(getTiempoDeEtapa(getNroDeEtapa())-minutos)/100+0x30;
              mensaje[10]=((getTiempoDeEtapa(getNroDeEtapa())-minutos)%100)/10+0x30; 
              mensaje[11]=(getTiempoDeEtapa(getNroDeEtapa())-minutos)%10+0x30;
              mensaje[12]='m';
              mensaje[13]='i';
              mensaje[14]='n';
              mensaje[15]='\0';
            }else if(((getTiempoDeEtapa(getNroDeEtapa())-minutos)/10) && ((getTiempoDeEtapa(getNroDeEtapa())-minutos)/100) != 1) {
              mensaje[9]=((getTiempoDeEtapa(getNroDeEtapa())-minutos)/10+0x30); 
              mensaje[10]=((getTiempoDeEtapa(getNroDeEtapa())-minutos)%10+0x30);
              mensaje[11]='m';
              mensaje[12]='i';
              mensaje[13]='n';
              mensaje[14]='\0';
            }else{
              mensaje[9]=(getTiempoDeEtapa(getNroDeEtapa())-minutos+0x30);
              mensaje[10]='m';
              mensaje[11]='i';
              mensaje[12]='n';
              mensaje[13]='\0';
             
             #endif 
              
       }
       
        if(!msj_VF)
         msj_VF = msjOutVF->addMessage(mensaje);
      }   
     }else {
            if(msj_VF){ 
              msjOutVF->deleteMessage(msj_VF);
               msj_VF = NULL; 
            }
            mensaje[0]='F';
            mensaje[1]='i';
            mensaje[2]='n';
            mensaje[3]='\0';
       
        if(!msj_VF)
         msj_VF = msjOutVF->addMessage(mensaje);
      }    
    
}




uchar ControlVF::getDecimales(){
  return _sensor.getDecimales();
}



int Te_MES_ANT(ControlVF *_self){
 ControlVF * self=_self; 
  
  if((self->getNroDeEtapa())>1){
      return (self->getTempDeEtapa((self->getNroDeEtapa())-1)); 
   }else{
      return 0;
   }
}

void procesarVF(void * a){
 char Kdec;
 long tempActVF=0;
 static char contProtecRuido=0;
 static dword rampa_mestaTime=0;
 ControlVF * self=(ControlVF*)a; 
 
  self->procesCartelesVF();
 
  if(self->getModoVF() == RUN){   //estoy corriendo?
 
   rampa_mestaTime++;
   
   if((self->getMinutos()))
      if(rampa_mestaTime>(60*(self->getMinutos())))
          (self->setMinutos((self->getMinutos()+1)));
/* calculo de la temperatura de la rampa cada 1 segundos y             */
/* calculo del tiempo transcurrido una ves llegado a la temp de meseta */  
                              
     
 /*/////////////////calculo del setpoint(tmpAct)/////////////// */
  
   if(self->getEstadoVF() == RAMPA) {                                                     //si, es rampa?
    
      if((self->getDecimales()) == 0)                                             //si, pongo decimales
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
          SET_SP(self,tempActVF); 
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
          SET_SP(self,tempActVF); 
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
  self->setMinutos(0);
  self->setEstadoVF(RAMPA);
  tempActVF=0;
  SET_SP(self,tempActVF);   
} 


}

