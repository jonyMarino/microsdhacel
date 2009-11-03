
#include "ValvulaProporcional.hpp"
#include "PWM.hpp"



ValvulaProporcional::ValvulaProporcional(struct ManejadorMemoria &_manejadorMemoria,ConfValvulaProporcional* conf,byte * puertoApertura,int bitApertura,byte * puertoCierre,int bitCierre):manejadorMemoria(_manejadorMemoria){
  this->conf=conf;
  //this->conf->tiempoAbierto=10;
  //this->conf->bandaMuerta=0;
  this->puertoApertura =  puertoApertura;
  this->puertoCierre =  puertoCierre ;
  this->mascaraApertura = 1<<bitApertura;
  this->mascaraCierre = 1<<bitCierre;
  this->timeCloseInit = (this->getTiempoAbierto(this) + FACTOR_SEGURIDAD)*1000/10;   //calculo el tiempo de cierre inicial(en milisegundos),divido por 10 por que cada 10ms actualizo
  timeActual = 0;
  setTiempoAbierto(this,this->conf->tiempoAbierto);
 newAlloced(&timer,/*&MethodTimer*/&RlxMTimer,(ulong)10,onCheckear,this);
 
}

static void ValvulaProporcional::onCheckear(void*_self)
{
  //cada 10ms es llamada 
  ValvulaProporcional * self = (ValvulaProporcional *)_self;
  bool flagBanda;
  word timesOpenClose,timesMuerto;
  word potencia_vp =self->_potencia;//self->getPotencia();
  if((self->timeCloseInit)>0){
    (self->timeCloseInit)--;
    self->cerrar();  // inicio cerrando durante el tiempo "timeCloseInit"
    return;
  } else if(potencia_vp == 1000)
            self->abrir();
         else if(potencia_vp == 0)
            self->detener();
               else{
                 timesOpenClose=potencia_vp*(self->conf->tiempoAbierto);  //tiempo en milisegundos
                 timesMuerto=(self->conf->bandaMuerta)*1000;
                 if((timesOpenClose>(self->timeActual))) {
                  self->abrir();
                  self->timeActual += 10;
                  flagBanda=FALSE;
                 }
                 else if((timesOpenClose<(self->timeActual))) {
                        self->cerrar();
                        self->timeActual -= 10;
                        flagBanda=TRUE;
                 }
                       else
                        self->detener(); 
               }
               
               if(timesMuerto!=0 && flagBanda==TRUE)
                if((timesOpenClose==self->timeActual)||(timesOpenClose<(self->timeActual+timesMuerto))||(timesOpenClose>(self->timeActual-timesMuerto)))
                   self->detener(); 
               
}
  

unsigned int ValvulaProporcional::getTiempoAbierto(void*_self) {
  ValvulaProporcional * self = (ValvulaProporcional *)_self;
  return _MANEJADOR_MEMORIA_GET_WORD(&(self->manejadorMemoria),&self->conf->tiempoAbierto);
}

unsigned char ValvulaProporcional::setTiempoAbierto(void*_self,unsigned int value) {
  ValvulaProporcional * self = (ValvulaProporcional *)_self;
  return _MANEJADOR_MEMORIA_SET_WORD(&self->manejadorMemoria,&self->conf->tiempoAbierto,(uchar)value);
}

unsigned int ValvulaProporcional::getBandaMuerta(void*_self) {
  ValvulaProporcional * self = (ValvulaProporcional *)_self;
  return _MANEJADOR_MEMORIA_GET_WORD(&self->manejadorMemoria,&self->conf->bandaMuerta);
}

unsigned char ValvulaProporcional::setBandaMuerta(void*_self,unsigned int value) {
  ValvulaProporcional * self = (ValvulaProporcional *)_self;
  return _MANEJADOR_MEMORIA_SET_WORD(&self->manejadorMemoria,&self->conf->bandaMuerta,value);
}

unsigned int ValvulaProporcional::getLimiteSuperiorTiempoAbierto(void*_self)
{
  return MAX_TIEMPOABIERTO;
}

unsigned int ValvulaProporcional::getLimiteSuperiorBandaMuerta(void*_self)
{
  return MAX_BANDAMUERTA;
}

unsigned int ValvulaProporcional::getPotencia()
{
  unsigned int potenciaActual;
  potenciaActual = (long)((timeActual)/(conf->tiempoAbierto)); // ya que timeActual esta en miliseg y tiempoAbierto en seg, no multiplico por 1000
  
  //if(timeActual!=0)
    return potenciaActual;
  //else
    //return _potencia;
}

void ValvulaProporcional::setPotencia(unsigned int potencia) 
{
 if(potencia<0 || potencia>1000)  
    return; //error
    
  _potencia=potencia;
}

TipoSalida ValvulaProporcional::getTipoSalida() 
{
  return SALIDA_PROPORCIONAL;
}

void ValvulaProporcional::setTipoSalida(TipoSalida tipoSalida) 
{
  return;
}

bool ValvulaProporcional::getConectada(){
  return 1;
}

void ValvulaProporcional::setConectada(bool conectada){
  return;
}

void ValvulaProporcional::cerrar() 
{
  clrReg8Bits(*(puertoApertura),(mascaraApertura));                           
  setReg8Bits(*(puertoCierre), (mascaraCierre));
  status=CERRANDO; //cerrando valvula
}

void ValvulaProporcional::abrir() 
{
  clrReg8Bits(*(puertoCierre),(mascaraCierre));                           
  setReg8Bits(*(puertoApertura),(mascaraApertura));
  status=ABRIENDO;  //abriendo valvula
}

void ValvulaProporcional::detener() 
{
  clrReg8Bits(*(puertoCierre), (mascaraCierre));                           
  clrReg8Bits(*(puertoApertura),(mascaraApertura));
  status=DETENIDA; //valvula detenida
}

char ValvulaProporcional::getStatus(){
  return status;
}

