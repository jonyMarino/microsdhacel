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

#include "PE_Types.h"
#include "funciones.h"
#include "IFsh10.h"
#include "ControlPID.h"
#include "RlxMTimer.h"
#include "ManejadorMemoria.h"

#pragma DATA_SEG PID_DATA                                            
#pragma CODE_SEG PID_CODE
#pragma CONST_SEG DEFAULT 

#define MAX_INTEGRAL 9999
#define MAX_DERIVADA 600


void PID_DefConstructor(void * self,va_list * args);
void PID_OnSensNewVal(void * self);

const struct TControlClass ControlPID={
  CLASS_INITIALIZATION(Class,ControlPID,Object,PID_DefConstructor,Object_dtor,Object_differ,Object_puto),  
  PID_getConfSP,
  NULL,
  PID_setConfSP,
  PID_OnSensNewVal
};


extern struct ManejadorMemoria *const pFlash;


void PID_ActValCont(void * self);

/*
** ===================================================================
**     Method      :  PID_Constructor 
**     Description :  Constructor del control PID
** ===================================================================
*/
void PID_Constructor(void * self,ControlConf * conf,struct SensorDecLim * sensor,struct ISalida * salida){
  struct ControlPID * _cont = (struct ControlPID *)self;

  _cont->_conf=conf;
  _cont->sensor=sensor;
  _cont->salida=salida;
  _cont->suminteg=0;
  _cont->buffer_deriv=0;
  _cont->OnTipoSalidaChange=NULL;
  
  newAlloced(&_cont->metodoOnNuevaMedicion,&Method,PID_OnSensNewVal,_cont);
  Sensor_addNuevaMedicionListener(sensor,&_cont->metodoOnNuevaMedicion);
  MedidorFunciones_setDeltaTiempo(_Sensor_getMeasurePeriod(sensor)); 
  
 /* if(time_desc!=0){    
    
    _cont->timerDesconexion= new(&RlxMTimer,(ulong)time_desc,PID_FstConect,self);  
    if(_cont->timerDesconexion)
      PID_Disconect(_cont);
    else
      PID_Conect(_cont);  
  }else
    PID_Conect(_cont);
   */
  set_SalControl(_cont,get_SalControl(_cont)); 	 

}

/*
** ===================================================================
**     Method      :  PID_DefConstructor 
**     Description :  Constructor por defecto del control PID
** ===================================================================
*/
void PID_DefConstructor(void * self,va_list * args){
  PID_Constructor(self,va_arg(*args,ControlConf *),va_arg(*args,struct SensorDecLim *),va_arg(*args,struct ISalida *));  
}

/*
** ===================================================================
**     Method      :  PID_AddOnTSalChange 
**     Description :  Agrega evento de cambio del Tipo de salida
** ===================================================================
*/
void PID_AddOnTSalChange(void * _self,void(*method)(void*,void*),void * Obj){
  struct ControlPID * _cont = (struct ControlPID *)_self;  
  
  if(!_cont->OnTipoSalidaChange)
    _cont->OnTipoSalidaChange=new MethodContainer(); 
  
  {
  void * methodTmp = _new(&Method,method,Obj);    
  _cont->OnTipoSalidaChange->add(methodTmp);
  }
  (*method)(Obj,_self);
}
/*
** ===================================================================
**     Method      :  PID_Disconect 
**     Description :  Desactiva la salida del PID
** ===================================================================
*/
void PID_Disconect(void * self){
  struct ControlPID * _cont =(struct ControlPID *) self;
 
  setConectada(_cont->salida,FALSE);
}



/*
** ===================================================================
**     Method      :  PID_Conect 
**     Description :  Activa la salida del PID
** ===================================================================
*/
void PID_Conect(void * self){
  struct ControlPID * _cont = (struct ControlPID *)self;
  
  setConectada(_cont->salida,TRUE);  
}
/*
** ===================================================================
**     Method      :  PID_isConnected 
**     Description :  Activa la salida del PID
** ===================================================================
*/
bool PID_isConnected(void * self){
  struct ControlPID * _cont = (struct ControlPID *)self;
  return getConectada(_cont->salida);
}

/*
** ===================================================================
**     Method      :  PID_es_pid 
**     Description :  Determina si se esta como PID o on-off
** ===================================================================
*/
bool PID_es_pid(void * self){
  struct ControlPID * _cont = (struct ControlPID *)self;
  
  return _cont->TipoControl==CNTR_PID;  
}

/*
** ===================================================================
**     Method      :  PID_OnSensNewVal 
**     Description :  Funcion de Evento de nuevo valor del sensor
** ===================================================================
*/
void PID_OnSensNewVal(void * self){
  struct ControlPID * _cont = (struct ControlPID *)self;
  
  PID_ActValCont(_cont);
  PID_setDutyControl(_cont);
  
}

/*
** ===================================================================
**     Method      :  PID_getOP_SP 
**     Description :  Obtiene el valor del set point que se utiliza 
**     para las  OPeraciones de calculo del control
** ===================================================================
*/
/*int PID_getOP_SP(struct ControlPID * _cont){
  return _Sensor_AdaptVal(_cont->sensor,PID_getConfSP(_cont));
}
*/
/*
** ===================================================================
**     Method      :  PID_getOP_H 
**     Description :  Obtiene el valor de histeresis que se utiliza 
**     para las OPeraciones de calculo del control
** ===================================================================
*/
/*int PID_getOP_H(struct ControlPID * _cont){
  return _Sensor_AdaptVal(_cont->sensor,_cont->_conf->iHisteresis);
}
 */
/*
** ===================================================================
**     Method      :  PID_getOP_Res 
**     Description :  Obtiene el valor del reset que se utiliza 
**     para las OPeraciones de calculo del control
** ===================================================================
*/
/*int PID_getOP_Res(struct ControlPID * _cont){
  return _Sensor_AdaptVal(_cont->sensor,_cont->_conf->iReset);
}
*/
/*
** ===================================================================
**     Method      :  PID_ActValCont 
**     Description :  Actualiza el valor de control
** ===================================================================
*/
void PID_ActValCont(void * self){
  struct ControlPID * _cont = (struct ControlPID *)self;
  int sp= PID_getConfSP(_cont);
  int vp= _Getter_getVal(_cont->sensor);
  int h= get_H_Control(_cont); 
  int res= get_Reset(_cont); 
  int In; 
  int Dr;
  int Pr;

//Integral    
    In= integral(vp,
                 sp,
                 h/2,		 //Ancho de Banda superior
                 -h/2,		 //Ancho de Banda inferior
                 (PID_es_pid(_cont))?_cont->_conf->iIntegral:0,	 //Constante de integracion
                 &_cont->suminteg
                 );

//Derivada												  	
    Dr = derivada   (vp,                 //derivada
                     _cont->val_ant,
                     (PID_es_pid(_cont))?_cont->_conf->iDerivada:0,
							       &_cont->buffer_deriv
								     );
		
		_cont->val_ant=vp;

//Proporcional
    Pr = proporcional (vp,								//proporcional
                       res,
											 sp
											 );


//Valor final de control
    _cont->ValControl= In+Pr+Dr;											  //variable de control

}

/*
** ===================================================================
**     Method      :  PID_setDutyControl 
**     Description :  Setea el duty de salida
** ===================================================================
*/
void PID_setDutyControl(void * self){
  struct ControlPID * _cont = (struct ControlPID *)self;
  int dutytmp;
  int h= get_H_Control(_cont);
  
  if(!PID_isConnected(_cont))
    return;  
  
  if (_cont->_conf->eSalidaControl == _MAN){
     dutytmp=_cont->_conf->iPotenciaManual; 
  } else{ 
        if (PID_es_pid(_cont))               //Estoy en PID
          dutytmp = duty_prop(_cont->ValControl, 
                              h,
															_cont->_conf->iPotenciaInf,
															_cont->_conf->iPotenciaSup
                              );
        else{
//            if (_cont->_conf->eSalidaControl == _REF)
//		          dutytmp = 1000-duty;
//            else  
//              dutytmp = duty;
            dutytmp = duty_onoff(_cont->ValControl, 
                            h 
                           );
            if(dutytmp<0)		 // No actualizar
              return;               
        }
  }

  if (_cont->_conf->eSalidaControl == _REF)
    dutytmp = 1000-dutytmp;

  setPotenciaSalida(_cont->salida,dutytmp);			//seteo el duty de salida     
      
}

/*
** ===================================================================
**     Method      :  PID_getDuty 
**     Description :  Obtiene el duty de salida
** ===================================================================
*/
int PID_getDuty(void * self){
  struct ControlPID * _cont = (struct ControlPID *)self;
  return getPotencia(_cont->salida);
}

/*
** ===================================================================
**     Method      :  PID_getSal 
**     Description :  Obtiene un puntero a la salida
** ===================================================================
*/
struct ISalida* PID_getSal(void * self){
  struct ControlPID * _cont = (struct ControlPID *)self;
  return _cont->salida;
}


/*
** ===================================================================
**     Method      :  PID_getSensor 
**     Description :  Obtiene el sensor utilizado por el control
** ===================================================================
*/
struct Sensor *PID_getSensor(void * self){
  struct ControlPID * _cont = (struct ControlPID *)self;
  return (struct Sensor *)_cont->sensor;  
}
/*
** ===================================================================
**     Method      :  PID_setTipoControl 
**     Description :  Funcion para setear el tipo de salida en on-off (salida independiente del periodo)
** ===================================================================
*/

T_TipoControl PID_getTipoControl(void * self){
  struct ControlPID * _cont = (struct ControlPID *)self;  
  return _cont->TipoControl; 
}

void PID_setTipoControl(void * self,T_TipoControl TipControl){
  struct ControlPID * _cont = (struct ControlPID *)self;
    
    _cont->TipoControl=TipControl;
    if(TipControl==CNTR_PID){
      _setTipoSalida(_cont->salida,SALIDA_PROPORCIONAL);
    }else{
      setTipoSalida(_cont->salida,SALIDA_ONOFF);  
    }
}

/*
** ===================================================================
**     Method      :  PID_getModSal 
**     Description :  MAN - REF -CAL
** ===================================================================
*/
T_SalidaControl PID_getModSal(void * self){
  struct ControlPID * _cont = (struct ControlPID *)self;
  return _cont->intModSalida; 
}

/*
** ===================================================================
**     Method      :  PID_getModSal 
**     Description :  MAN - REF -CAL
** ===================================================================
*/
void PID_setModSal(void * self,T_SalidaControl val){
  struct ControlPID * _cont = (struct ControlPID *)self;  
  _cont->intModSalida = val;    
  if(val==_MAN){
      PID_setTipoControl(_cont,CNTR_PID);
  }else{
      PID_setTipoControl(_cont,get_TipoControl(self));
  }

  if(_cont->OnTipoSalidaChange){
    LinkedList::LinkedListIterator it;
    _cont->OnTipoSalidaChange->linkedListIterator(&it); 
    
    while(it.hasNext()){    
      const struct Method* mo= (const struct Method*)it.next();
      (*(void(*)(void*,void*))mo->pmethod)(mo->Obj,self);
    }
  
  }
}

/*
** ===================================================================
**     Method      :  PID_getValControl 
**     Description :  Obtiene el valor de control (In+Dr+Pr)
** ===================================================================
*/
int PID_getValControl(void * self){ 
  struct ControlPID * _cont = (struct ControlPID *)self;
  return _cont->ValControl;
}
/*
** ===================================================================
**     Method      :  PID_getDec 
**     Description :  Obtiene los decimales del sensor usado
** ===================================================================
*/
uchar PID_getDec(void * self) {
  struct ControlPID * _cont = (struct ControlPID *)self;
  return _getDec(_cont->sensor);
}

/*
** ===================================================================
**     Method      :  Cntrl_getSP 
**     Description :  Set Point Configuracion
** ===================================================================
*/
int PID_getLimInfSP(void * self){
  struct ControlPID * _cont = (struct ControlPID *)self;
  return _cont->_conf->iLimInfSP;    
}

int PID_getLimSupSP(void * self){
  struct ControlPID * _cont = (struct ControlPID *)self;
  return  _cont->_conf->iLimSupSP;    
}

int PID_getConfSP(void * self){
  struct ControlPID * _cont = (struct ControlPID *)self;
  return  _MANEJADOR_MEMORIA_GET_WORD(pFlash,(const word*)&_cont->_conf->iSP);
}



byte PID_setConfSP(void * self,int val){
  struct ControlPID * _cont = (struct ControlPID *)self;
  byte err=_MANEJADOR_MEMORIA_SET_WORD(pFlash,(const word*)& _cont->_conf->iSP,val);
  return err;
}


/*
** ===================================================================
**     Method      :  set_LimInf_SP 
**     Description :  Lim Inf y Sup del SP
** ===================================================================
*/
byte set_LimInf_SP(void * self,int val){
  struct ControlPID * _cont = (struct ControlPID *)self;
  byte err=_MANEJADOR_MEMORIA_SET_WORD(pFlash,(const word*)& _cont->_conf->iLimInfSP,val);
  if(!err)
    if( _cont->_conf->iSP<val)
      err= Cntrl_setSP(_cont,val);
  return err;
}

byte set_LimSup_SP(void * self,int val){
  struct ControlPID * _cont = (struct ControlPID *)self;
  byte err=_MANEJADOR_MEMORIA_SET_WORD(pFlash,(const word*)& _cont->_conf->iLimSupSP,val); 
  if(!err)
    if( _cont->_conf->iSP>val)
      err= Cntrl_setSP(_cont,val);
  return err;   
}
int getLimInfSensorControl(void * self){
  struct ControlPID * _cont = (struct ControlPID *)self;
  return _Sensor_getLimInf(_cont->sensor);
}

int getLimSupSensorControl(void * self){
  struct ControlPID * _cont = (struct ControlPID *)self;
  return PID_getLimSupSP(_cont);
}

int get_LimInf_LimSupSP(void * self){
  struct ControlPID * _cont = (struct ControlPID *)self;
  return PID_getLimInfSP(_cont);
}

int get_LimSup_LimSupSP(void * self){
  struct ControlPID * _cont = (struct ControlPID *)self;
  return _Sensor_getLimSup(_cont->sensor);
}

/*
** ===================================================================
**     Method      :  get_Reset 
**     Description :  
** ===================================================================
*/

int get_Reset(void * self){
  struct ControlPID * _cont = (struct ControlPID *)self;
  return  _cont->_conf->iReset;
}

byte set_Reset(void * self,int val){
  struct ControlPID * _cont = (struct ControlPID *)self;
  return _MANEJADOR_MEMORIA_SET_WORD(pFlash,(const word*)& _cont->_conf->iReset,val);
}

/*
** ===================================================================
**     Method      :  get_TipoControl 
**     Description :  Tipo de control
** ===================================================================
*/
int  get_TipoControl(void * self){
  struct ControlPID * _cont = (struct ControlPID *)self;
  return _MANEJADOR_MEMORIA_GET_BYTE(pFlash,&_cont->_conf->eTipoControl);
}

byte set_TipoControl(void * self,int tc){
  struct ControlPID * _cont = (struct ControlPID *)self;
  byte err=_MANEJADOR_MEMORIA_SET_BYTE(pFlash,(const byte*)& _cont->_conf->eTipoControl,tc); 
  if(!err)   
      PID_setModSal(_cont,tc);    
  return err;
}

int get_LimSup_TipoControl(void){
  return MAX_VALUE_TIPO_CONTROL;
}

/*
** ===================================================================
**     Method      :  get_SalControl 
**     Description :  Tipo de salida de Control
** ===================================================================
*/
int get_SalControl(void * self){
  struct ControlPID * _cont = (struct ControlPID *)self;
  return  _cont->_conf->eSalidaControl; 
}

byte set_SalControl(void * self,int val){
  struct ControlPID * _cont = (struct ControlPID *)self;
  byte err= _MANEJADOR_MEMORIA_SET_BYTE(pFlash,(const byte*)& _cont->_conf->eSalidaControl,val);
  if(!err){    
    PID_setModSal(_cont,val);
  }
  return err;
}

int get_LimSup_SalControl(void * self){
  struct ControlPID * _cont = (struct ControlPID *)self;
  return MAX_VALUE_SALIDA_CONTROL; 
}

/*
** ===================================================================
**     Method      :  get_H_Control 
**     Description :  Histeresis
** ===================================================================
*/
int get_H_Control(void * self){
  struct ControlPID * _cont = (struct ControlPID *)self;
  return  (get_TipoControl(_cont)==CNTR_ONOFF)?-_cont->_conf->iHisteresis:_cont->_conf->iHisteresis;  
}

byte set_H_Control(void * self,int val){
  struct ControlPID * _cont = (struct ControlPID *)self;
  byte err;  
  err=_MANEJADOR_MEMORIA_SET_WORD(pFlash,(const word*)& _cont->_conf->iHisteresis,abs(val));
  
  if(!err){
      if(val<0)
        set_TipoControl(_cont,CNTR_ONOFF);  
      else
        set_TipoControl(_cont,CNTR_PID);
  }
  
  return err;
}

/*
** ===================================================================
**     Method      :  get_integral 
**     Description :  Constante de integracion
** ===================================================================
*/
int get_integral(void * self){
  struct ControlPID * _cont = (struct ControlPID *)self;
  return _cont->_conf->iIntegral;
}

byte set_integral(void * self,int val){
  struct ControlPID * _cont = (struct ControlPID *)self;
  byte err= _MANEJADOR_MEMORIA_SET_WORD(pFlash,(const word*)&_cont->_conf->iIntegral,val);
  if(!err)
    _cont->suminteg=0;
  return err;
}

int get_LimSup_integral(void*){
  return MAX_INTEGRAL;
}

/*
** ===================================================================
**     Method      :  get_derivada 
**     Description :  Constante de derivacion
** ===================================================================
*/
int get_derivada(void * self){
  struct ControlPID * _cont = (struct ControlPID *)self;
  return _cont->_conf->iDerivada;
}

byte set_derivada(void * self,int val){
  struct ControlPID * _cont = (struct ControlPID *)self;
  byte err= _MANEJADOR_MEMORIA_SET_WORD(pFlash,(const word*)&_cont->_conf->iDerivada,val);
  return err;
}

int get_LimSup_derivada(void*a){
  return MAX_DERIVADA;
}

/*
** ===================================================================
**     Method      :  get_PotenciaInf 
**     Description :  Limite Inferior de Potencia de Salida
** ===================================================================
*/
int get_PotenciaInf(void * self){
  struct ControlPID * _cont = (struct ControlPID *)self;
  return _cont->_conf->iPotenciaInf;
}

byte set_PotenciaInf(void * self,int val){
  struct ControlPID * _cont = (struct ControlPID *)self;
  return _MANEJADOR_MEMORIA_SET_WORD(pFlash,(const word*)&_cont->_conf->iPotenciaInf,val);
}

int get_LimInf_PotenciaInf(void*a){
  return MIN_POTENCIA;
}
int get_LimSup_PotenciaInf(void * self){
  struct ControlPID * _cont = (struct ControlPID *)self;
  return _cont->_conf->iPotenciaSup;
}

/*
** ===================================================================
**     Method      :  get_PotenciaSup 
**     Description :  Limite Superior de Potencia de Salida
** ===================================================================
*/
int get_PotenciaSup(void * self){
  struct ControlPID * _cont = (struct ControlPID *)self;
  return _cont->_conf->iPotenciaSup;
}

byte set_PotenciaSup(void * self,int val){
  struct ControlPID * _cont = (struct ControlPID *)self;
  return _MANEJADOR_MEMORIA_SET_WORD(pFlash,(const word*)&_cont->_conf->iPotenciaSup,val);
}

int get_LimInf_PotenciaSup(void * self){
  struct ControlPID * _cont = (struct ControlPID *)self;
  return _cont->_conf->iPotenciaInf;
}
int get_LimSup_PotenciaSup(void*a){
  return MAX_POTENCIA;
}
/*
** ===================================================================
**     Method      :  get_PotenciaManual 
**     Description :  Valor de la Potencia de Salida en Manual
** ===================================================================
*/
int get_PotenciaManual(void * self){
  struct ControlPID * _cont = (struct ControlPID *)self;
  return _cont->_conf->iPotenciaManual;
}

byte set_PotenciaManual(void * self,int val){
  struct ControlPID * _cont = (struct ControlPID *)self;
  return _MANEJADOR_MEMORIA_SET_WORD(pFlash,(const word*)&_cont->_conf->iPotenciaManual,val);
}

int get_LimInf_PotenciaManual(void * self){
  struct ControlPID * _cont = (struct ControlPID *)self;
  return _cont->_conf->iPotenciaInf;
}
int get_LimSup_PotenciaManual(void * self){
  struct ControlPID * _cont = (struct ControlPID *)self;
  return _cont->_conf->iPotenciaSup;
}
 
#pragma CODE_SEG PID_CODE 