/*MODULE: ControlPID.c*/
/*
**     Filename  : ControlPID.C
**     Project   : Controlador
**     Processor : MC9S12GC32CFU
**     Version   : 0.0.4
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 13/03/2008, 10:53
**     Abstract  :
**							Control PID con Eventos
*/
#include <stdarg.h>
#include <stddef.h>		
#include <stdlib.h>
#include "Sensores.h"
#include "ControlPID.hpp"
#include "controlmath.h"
//#include "funciones.h"

#pragma DATA_SEG ControlPID_DATA                                            
#pragma CODE_SEG ControlPID_CODE
#pragma CONST_SEG DEFAULT 


/*
** ===================================================================
**     Method      :  ControlPID::Constructor 
**     Description :  Constructor del control PID
** ===================================================================
*/
ControlPID::ControlPID(Sensor& _sensor,ISalida& _salida,const ConfiguracionControl& _configuracion):Lazo(_sensor),salida(_salida),configuracion(_configuracion){

  sumatoriaIntegral=0;
  bufferDerivada=0;
  onTipoSalidaChange=NULL;
  
  //MedidorFunciones_setDeltaTiempo(_Sensor_getMeasurePeriod(sensor)); 
  
 /* if(time_desc!=0){    
    
    _cont->timerDesconexion= new(&RlxMTimer,(ulong)time_desc,ControlPID::FstConect,self);  
    if(_cont->timerDesconexion)
      ControlPID::Disconect(_cont);
    else
      ControlPID::Conect(_cont);  
  }else
    ControlPID::Conect(_cont);
   */
  setTipoSalida(getTipoSalida()); 	 

}

/*
** ===================================================================
**     Method      :  ControlPID::AddOnTSalChange 
**     Description :  Agrega evento de cambio del Tipo de salida
** ===================================================================
*/
void ControlPID::addOnTipoSalidaListener(struct Method& metodo){
  if(!onTipoSalidaChange)
    onTipoSalidaChange=new MethodContainer(); 
   
  onTipoSalidaChange->add((void*)&metodo);
}



/*
** ===================================================================
**     Method      :  ControlPID::Disconect 
**     Description :  Desactiva la salida del PID
** ===================================================================
*/
void ControlPID::desconectar(){
  salida.setConectada(FALSE);
}



/*
** ===================================================================
**     Method      :  ControlPID::Conect 
**     Description :  Activa la salida del PID
** ===================================================================
*/
void ControlPID::conectar(){
  salida.setConectada(TRUE);  
}
/*
** ===================================================================
**     Method      :  ControlPID::isConnected 
**     Description :  Activa la salida del PID
** ===================================================================
*/
bool ControlPID::isConectado(){
  return salida.getConectada();
}

/*
** ===================================================================
**     Method      :  ControlPID::es_pid 
**     Description :  Determina si se esta como PID o on-off
** ===================================================================
*/
bool ControlPID::isPID(){
  return getTipoControl()==CNTR_PID;  
}

/*
** ===================================================================
**     Method      :  ControlPID::OnSensNewVal 
**     Description :  Funcion de Evento de nuevo valor del sensor
** ===================================================================
*/
void ControlPID::onNuevoValorSensor(){
  actualizarValorControl();
  setDutyControl();
}


/*
** ===================================================================
**     Method      :  ControlPID::ActValCont 
**     Description :  Actualiza el valor de control
** ===================================================================
*/
void ControlPID::actualizarValorControl(){
  int sp= getConfiguracionSetPoint();
  int vp= getSensor().getVal();
  int h= getHisteresis(); 
  int res= getReset(); 
  int In; 
  int Dr;
  int Pr;

//Integral    
    In= integral(vp,
                 sp,
                 h/2,		 //Ancho de Banda superior
                 -h/2,		 //Ancho de Banda inferior
                 (isPID())?configuracion.getIntegral():0,	 //Constante de integracion
                 &sumatoriaIntegral
                 );

//Derivada												  	
    Dr = derivada   (vp,                 //derivada
                     valorAnterior,
                     (isPID())?configuracion.getDerivada():0,
							       &bufferDerivada
								     );
		
		valorAnterior=vp;

//Proporcional
    Pr = proporcional (vp,								//proporcional
                       res,
											 sp
											 );


//Valor final de control
    valorControl= In+Pr+Dr;											  //variable de control

}

/*
** ===================================================================
**     Method      :  ControlPID::setDutyControl 
**     Description :  Setea el duty de salida
** ===================================================================
*/
void ControlPID::setDutyControl(){

  int dutytmp;
  int h= getHisteresis();
  
  if(!isConectado())
    return;  
  
  if (/*configuracion.getTipoSalida()*/modoSalida == _MAN){
     dutytmp= configuracion.getPotenciaManual(); 
  } else{ 
        if (isPID())               //Estoy en PID
          dutytmp = duty_prop(valorControl, 
                              h,
															configuracion.getLimiteInferiorPotencia(),
															configuracion.getLimiteSuperiorPotencia()
                              );
        else{

            dutytmp = duty_onoff(valorControl,h );
            
            if(dutytmp<0)		 // No actualizar
              return;               
        }
  }

  if (/*configuracion.getTipoSalida()*/ modoSalida == _REF)
    dutytmp = 1000-dutytmp;

  salida.setPotencia(dutytmp);			//seteo el duty de salida     
      
}

/*
** ===================================================================
**     Method      :  ControlPID::getDuty 
**     Description :  Obtiene el duty de salida
** ===================================================================
*/
int ControlPID::getDuty(){
  return salida.getPotencia();
}

/*
** ===================================================================
**     Method      :  ControlPID::getSal 
**     Description :  Obtiene un puntero a la salida
** ===================================================================
*/
ISalida& ControlPID::getSalida(){
  return salida;
}

/*
** ===================================================================
**     Method      :  ControlPID::setTipoControl 
**     Description :  Funcion para setear el tipo de salida en on-off (salida independiente del periodo)
** ===================================================================
*/

ControlPID::TTipoControl ControlPID::getTipoControl(){ 
  return configuracion.getTipoControl(); 
}

void ControlPID::setTipoControl(ControlPID::TTipoControl tipoControl){
    configuracion.setTipoControl(tipoControl);
    if(tipoControl==CNTR_PID){
      salida.setTipoSalida(SALIDA_PROPORCIONAL);
    }else{
      salida.setTipoSalida(SALIDA_ONOFF);  
    }
}

/*
** ===================================================================
**     Method      :  ControlPID::getModSal 
**     Description :  MAN - REF -CAL
** ===================================================================
*/
ControlPID::TSalida ControlPID::getModoSalida(){
  return modoSalida;
  //return configuracion.getTipoSalida();  
}

/*
** ===================================================================
**     Method      :  ControlPID::getModSal 
**     Description :  MAN - REF -CAL
** ===================================================================
*/
void ControlPID::setModoSalida(TSalida val){ 
  modoSalida = val;    
  configuracion.setTipoSalida((int)val);
  if(modoSalida==_MAN){
      setTipoControl(CNTR_PID);
  }else{
      setTipoControl(getTipoControl());
  }

  if(onTipoSalidaChange){
    LinkedList::LinkedListIterator it;
    onTipoSalidaChange->linkedListIterator(&it); 
    
    while(it.hasNext()){    
      const struct Method* mo= (const struct Method*)it.next();
      (*(void(*)(void*,void*))mo->pmethod)(mo->obj,this);
    }
  
  }
}

/*
** ===================================================================
**     Method      :  ControlPID::getValControl 
**     Description :  Obtiene el valor de control (In+Dr+Pr)
** ===================================================================
*/
int ControlPID::getValorControl(){ 
  return valorControl;
}
/*
** ===================================================================
**     Method      :  ControlPID::getDec 
**     Description :  Obtiene los decimales del sensor usado
** ===================================================================
*/
uchar ControlPID::getDecimales() {
  return getSensor().getDecimales();
}

/*
** ===================================================================
**     Method      :  Cntrl_getSP 
**     Description :  Set Point Configuracion
** ===================================================================
*/
int ControlPID::getLimiteInferiorSetPoint(){
  return configuracion.getLimiteInferiorSetPoint();    
}

int ControlPID::getLimiteSuperiorSetPoint(){
  return  configuracion.getLimiteSuperiorSetPoint();    
}

int ControlPID::getConfiguracionSetPoint(){
  return  configuracion.getSetPoint();
}



void ControlPID::setConfiguracionSetPoint(int val){
  configuracion.setSetPoint(val);
}


/*
** ===================================================================
**     Method      :  set_LimInf_SP 
**     Description :  Lim Inf y Sup del SP
** ===================================================================
*/
void ControlPID::setLimiteInferiorSetPoint(int val){
  configuracion.setLimiteInferiorSetPoint(val);
  if( getConfiguracionSetPoint()<val)
    setConfiguracionSetPoint(val);
}

void ControlPID::setLimiteSuperiorSetPoint(int val){
  configuracion.setLimiteSuperiorSetPoint(val); 
  if( getConfiguracionSetPoint()>val)
      setConfiguracionSetPoint(val);  
}

int ControlPID::getLimiteInferiorSensor(){
  return getSensor().getLimiteInferior();
}

int ControlPID::getLimiteSuperiorSensor(){
  return getSensor().getLimiteSuperior();
}

int ControlPID::getLimiteInferiorDelLimiteSuperiorSetPoint(){
  return getLimiteInferiorSetPoint();
}

int ControlPID::getLimiteSuperiorDelLimiteSuperiorSetPoint(){
  return getSensor().getLimiteSuperior();
}

/*
** ===================================================================
**     Method      :  get_Reset 
**     Description :  
** ===================================================================
*/

int ControlPID::getReset(){
  return  configuracion.getReset();
}

void ControlPID::setReset(int val){
  configuracion.setReset(val);
}

/*
** ===================================================================
**     Method      :  get_TipoControl 
**     Description :  Tipo de control
** ===================================================================
*/
int  ControlPID::getConfiguracionTipoControl(){
  return configuracion.getTipoControl();
}

void ControlPID::setConfiguracionTipoControl(int val){
  configuracion.setTipoControl(val);
  setModoSalida(val);    
}

/*
** ===================================================================
**     Method      :  get_SalControl 
**     Description :  Tipo de salida de Control
** ===================================================================
*/
int ControlPID::getTipoSalida(){
  return  configuracion.getTipoSalida(); 
}

void ControlPID::setTipoSalida(int val){
  configuracion.setTipoSalida(val);   
  setModoSalida(val);
}

/*
** ===================================================================
**     Method      :  get_H_Control 
**     Description :  Histeresis
** ===================================================================
*/
int ControlPID::getHisteresis(){
  int h = configuracion.getHisteresis();
  return  (getTipoControl()==CNTR_ONOFF)?-h:h;  
}

void ControlPID::setHisteresis(int val){
  configuracion.setHisteresis(abs(val));
  if(val<0)
    setTipoControl(CNTR_ONOFF);  
  else
    setTipoControl(CNTR_PID);

}

/*
** ===================================================================
**     Method      :  get_integral 
**     Description :  Constante de integracion
** ===================================================================
*/
int ControlPID::getIntegral(){
  return configuracion.getIntegral();
}

void ControlPID::setIntegral(int val){
  configuracion.setIntegral(val);
  sumatoriaIntegral=0;
}

/*
** ===================================================================
**     Method      :  get_derivada 
**     Description :  Constante de derivacion
** ===================================================================
*/
int ControlPID::getDerivada(){
  return configuracion.getDerivada();
}

void ControlPID::setDerivada(int val){
  configuracion.setDerivada(val);
}

/*
** ===================================================================
**     Method      :  get_PotenciaInf 
**     Description :  Limite Inferior de Potencia de Salida
** ===================================================================
*/
int ControlPID::getLimiteInferiorPotencia(){
  return configuracion.getLimiteInferiorPotencia();
}

void ControlPID::setLimiteInferiorPotencia(int val){
  configuracion.setLimiteInferiorPotencia(val);
}

int ControlPID::getLimiteInferiorDelLimiteInferiorPotencia(){
  return MIN_POTENCIA;
}

int ControlPID::getLimiteSuperiorDelLimiteInferiorPotencia(){
  return configuracion.getLimiteSuperiorPotencia();
}

/*
** ===================================================================
**     Method      :  get_PotenciaSup 
**     Description :  Limite Superior de Potencia de Salida
** ===================================================================
*/
int ControlPID::getLimiteSuperiorPotencia(){
  return configuracion.getLimiteSuperiorPotencia();
}

void ControlPID::setLimiteSuperiorPotencia(int val){
  configuracion.setLimiteSuperiorPotencia(val);
}

int ControlPID::getLimiteInferiorDelLimiteSuperiorPotencia(){
  return configuracion.getLimiteInferiorPotencia();
}

int ControlPID::getLimiteSuperiorDelLimiteSuperiorPotencia(){
  return MAX_POTENCIA;
}
/*
** ===================================================================
**     Method      :  get_PotenciaManual 
**     Description :  Valor de la Potencia de Salida en Manual
** ===================================================================
*/
int ControlPID::getPotenciaManual(){
  return configuracion.getPotenciaManual();
}

void ControlPID::setPotenciaManual(int val){
  configuracion.setPotenciaManual(val);
}

int ControlPID::getLimiteInferiorPotenciaManual(){
  return configuracion.getLimiteInferiorPotencia();
}
int ControlPID::getLimiteSuperiorPotenciaManual(){
  return configuracion.getLimiteSuperiorPotencia();
}
 
#pragma CODE_SEG ControlPID_CODE 