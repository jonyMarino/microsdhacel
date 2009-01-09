/*MODULE: ControlPID.c*/
#include <stdarg.h>
#include <stddef.h>		
#include <stdlib.h>

#include "PE_Types.h"
#include "funciones.h"
#include "IFsh10.h"
#include "ControlPID0.0.1.h"

#define set_MainStaticText(str) {}
#define _cout set_MainStaticText

#define MAX_INTEGRAL 1000
#define MAX_DERIVADA 600


void PID_DefConstructor(void * self,va_list * args);

struct TControl TableControlPID={
    sizeof(struct ControlPID),
    PID_DefConstructor,
    NULL,
    NULL,
    NULL,
    PID_setSP
};

const void * ControlPID= &TableControlPID;


void PID_FstConect(void * self);
void PID_ActValCont(void * self);

/*
** ===================================================================
**     Method      :  PID_Constructor 
**     Description :  Constructor del control PID
** ===================================================================
*/
void PID_Constructor(void * self,void * conf,void * sensor,void* salida,int time_desc){
  struct ControlPID * _cont = self;

  _cont->_conf=conf;
  _cont->sensor=sensor;
  _cont->salida=salida;
  _cont->suminteg=0;
  _cont->buffer_deriv=0;
  
  
  PID_Disconect(_cont);
 
  set_SalControl(_cont,get_SalControl(_cont)); 	 

  _cont->PIDtimer= newObj(MethodTimer,(ulong)time_desc,PID_FstConect,self); 
  
  _cont->values=newObj(IntArray,3);
}

/*
** ===================================================================
**     Method      :  PID_DefConstructor 
**     Description :  Constructor por defecto del control PID
** ===================================================================
*/
void PID_DefConstructor(void * self,va_list * args){
  PID_Constructor(self,va_arg(*args,void*),va_arg(*args,void*),va_arg(*args,void*),va_arg(*args,int));  
}

/*
** ===================================================================
**     Method      :  PID_Disconect 
**     Description :  Desactiva la salida del PID
** ===================================================================
*/
void PID_Disconect(void * self){
  struct ControlPID * _cont = self;
  
  _cont->isConnected=FALSE;  
  _Salida_setDuty(_cont->salida,0);
}

/*
** ===================================================================
**     Method      :  PID_FstConect 
**     Description :  Libera el Timer y Activa la salida del PID
** ===================================================================
*/
void PID_FstConect(void * self){
  struct ControlPID * _cont = self;
  
  deleteObj(&_cont->PIDtimer);
  PID_Conect(self);
}
/*
** ===================================================================
**     Method      :  PID_Conect 
**     Description :  Activa la salida del PID
** ===================================================================
*/
void PID_Conect(void * self){
  struct ControlPID * _cont = self;
  
  _cont->isConnected=TRUE;  
}
/*
** ===================================================================
**     Method      :  PID_isConnected 
**     Description :  Activa la salida del PID
** ===================================================================
*/
bool PID_isConnected(void * self){
  struct ControlPID * _cont = self;
  return _cont->isConnected;
}

/*
** ===================================================================
**     Method      :  PID_es_pid 
**     Description :  Determina si se esta como PID o on-off
** ===================================================================
*/
bool PID_es_pid(void * self){
  struct ControlPID * _cont = self;
  
  return _cont->TipoControl==CNTR_PID;  
}

/*
** ===================================================================
**     Method      :  PID_Handler 
**     Description :  Funcion de Eventos
** ===================================================================
*/
void PID_Handler(void * self){
  struct ControlPID * _cont = self;
  
  if(! isnew(_cont->sensor) )
    return;
  
  PID_ActValCont(_cont);
  PID_setDutyControl(_cont);
  
}
/*
** ===================================================================
**     Method      :  PID_ActValCont 
**     Description :  Actualiza el valor de control
** ===================================================================
*/
void PID_ActValCont(void * self){
  struct ControlPID * _cont = self;
  int sp= _cont->_conf->iSP;
  int vp= _Getter_getVal(_cont->sensor);
  int In; 
  int Dr;
  int Pr;

//Integral    
    IntArray_Add(_cont->values,vp);
    In= int_Trapecios(IntArray_AsArray(_cont->values),
                 sp,
                 _cont->_conf->iHisteresis/2,		 //Ancho de Banda inferior
                 -(_cont->_conf->iHisteresis/2),		 //Ancho de Banda Superior
                 (PID_es_pid(_cont))?_cont->_conf->iIntegral:0,	 //Constante de integracion
                 &_cont->suminteg
                 );

//Derivada												  	
    Dr = -derivada3p (IntArray_AsArray(_cont->values),
                     (PID_es_pid(_cont))?_cont->_conf->iDerivada:0
//							       &_cont->buffer_deriv
								     );
//Proporcional
    Pr = proporcional (vp,								//proporcional
                       _cont->_conf->iReset,
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
  struct ControlPID * _cont = self;
  int dutytmp;

  if(!PID_isConnected(_cont))
    return;  
  
  if (_cont->_conf->eSalidaControl == _MAN){
     dutytmp=_cont->_conf->iPotenciaManual; 
  } else{ 
        if (PID_es_pid(_cont))               //Estoy en PID
          dutytmp = duty_prop(_cont->ValControl, 
                              _cont->_conf->iHisteresis,
															_cont->_conf->iPotenciaInf,
															_cont->_conf->iPotenciaSup
                              );
        else{
//            if (_cont->_conf->eSalidaControl == _REF)
//		          dutytmp = 1000-duty;
//            else  
//              dutytmp = duty;
            dutytmp = duty_onoff(_cont->ValControl, 
                            _cont->_conf->iHisteresis 
                           );
            if(dutytmp<0)		 // No actualizar
              return;               
        }
  }

  if (_cont->_conf->eSalidaControl == _REF)
    dutytmp = 1000-dutytmp;

  _Salida_setDuty(_cont->salida,dutytmp);			//seteo el duty de salida     
      
}


/*
** ===================================================================
**     Method      :  PID_getSensor 
**     Description :  Obtiene el sensor utilizado por el control
** ===================================================================
*/
const struct Sensor *PID_getSensor(void * self){
  struct ControlPID * _cont = self;
  return _cont->sensor;  
}
/*
** ===================================================================
**     Method      :  PID_setTipoControl 
**     Description :  Funcion para setear el tipo de salida en on-off (salida independiente del periodo)
** ===================================================================
*/

T_TipoControl PID_getTipoControl(void * self){
  struct ControlPID * _cont = self;  
  return _cont->TipoControl; 
}

void PID_setTipoControl(void * self,T_TipoControl TipControl){
  struct ControlPID * _cont = self;
    
    _cont->TipoControl=TipControl;
    if(TipControl==CNTR_PID){
      _Salida_OnOff(_cont->salida,FALSE);
    }else{
      _Salida_OnOff(_cont->salida,TRUE);  
    }
}

/*
** ===================================================================
**     Method      :  PID_getModSal 
**     Description :  MAN - REF -CAL
** ===================================================================
*/
T_SalidaControl PID_getModSal(void * self){
  struct ControlPID * _cont = self;
  return _cont->intModSalida; 
}

/*
** ===================================================================
**     Method      :  PID_getModSal 
**     Description :  MAN - REF -CAL
** ===================================================================
*/
void PID_setModSal(void * self,T_SalidaControl val){
  struct ControlPID * _cont = self;  
  _cont->intModSalida = val;    
  if(val==_MAN){
      PID_setTipoControl(_cont,CNTR_PID);
      _cout("MAn ");
  }else{
      PID_setTipoControl(_cont,_cont->_conf->eTipoControl);
  		_cout("");
  }
}

/*
** ===================================================================
**     Method      :  PID_getValControl 
**     Description :  Obtiene el valor de control (In+Dr+Pr)
** ===================================================================
*/
int PID_getValControl(void * self){ 
  struct ControlPID * _cont = self;
  return _cont->ValControl;
}
/*
** ===================================================================
**     Method      :  PID_getDec 
**     Description :  Obtiene los decimales del sensor usado
** ===================================================================
*/
uchar PID_getDec(void * self) {
  struct ControlPID * _cont = self;
  return _getDec(_cont->sensor);
}
/*
** ===================================================================
**     Method      :  PID_getSP 
**     Description :  Set Point Configuracion
** ===================================================================
*/
int PID_getLimInfSP(void * self){
  struct ControlPID * _cont = self;
  return _cont->_conf->iLimInfSP;    
}

int PID_getLimSupSP(void * self){
  struct ControlPID * _cont = self;
  return  _cont->_conf->iLimSupSP;    
}

int PID_getSP(void * self){
  struct ControlPID * _cont = self;
  return  _cont->_conf->iSP;
}

byte PID_setSP(void * self,int val){
  struct ControlPID * _cont = self;
  byte err=EscribirWord((word)& _cont->_conf->iSP,val);
  _cont->suminteg=0;
  return err;
}

/*
** ===================================================================
**     Method      :  set_LimInf_SP 
**     Description :  Lim Inf y Sup del SP
** ===================================================================
*/
byte set_LimInf_SP(void * self,int val){
  struct ControlPID * _cont = self;
  byte err=EscribirWord((word)& _cont->_conf->iLimInfSP,val);
  if(!err)
    if( _cont->_conf->iSP<val)
      err= PID_setSP(_cont,val);
  return err;
}

byte set_LimSup_SP(void * self,int val){
  struct ControlPID * _cont = self;
  byte err=EscribirWord((word)& _cont->_conf->iLimSupSP,val); 
  if(!err)
    if( _cont->_conf->iSP>val)
      err= PID_setSP(_cont,val);
  return err;   
}
int get_LimInf_LimInfSP(void * self){
  struct ControlPID * _cont = self;
  return _Sensor_getLimInf(_cont->sensor);
}

int get_LimSup_LimInfSP(void * self){
  struct ControlPID * _cont = self;
  return PID_getLimSupSP(_cont);
}

int get_LimInf_LimSupSP(void * self){
  struct ControlPID * _cont = self;
  return PID_getLimInfSP(_cont);
}

int get_LimSup_LimSupSP(void * self){
  struct ControlPID * _cont = self;
  return _Sensor_getLimSup(_cont->sensor);
}

/*
** ===================================================================
**     Method      :  get_Reset 
**     Description :  
** ===================================================================
*/

int get_Reset(void * self){
  struct ControlPID * _cont = self;
  return  _cont->_conf->iReset;
}

byte set_Reset(void * self,int val){
  struct ControlPID * _cont = self;
  return EscribirWord((word)& _cont->_conf->iReset,val);
}

/*
** ===================================================================
**     Method      :  get_TipoControl 
**     Description :  Tipo de control
** ===================================================================
*/
int  get_TipoControl(void * self){
  struct ControlPID * _cont = self;
  return  _cont->_conf->eTipoControl;
}

byte set_TipoControl(void * self,int tc){
  struct ControlPID * _cont = self;
  byte err=EscribirByte((word)& _cont->_conf->eTipoControl,tc); 
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
  struct ControlPID * _cont = self;
  return  _cont->_conf->eSalidaControl; 
}

byte set_SalControl(void * self,int val){
  struct ControlPID * _cont = self;
  byte err= EscribirByte((word)& _cont->_conf->eSalidaControl,val);
  if(!err){    
    PID_setModSal(_cont,val);
  }
  return err;
}

int get_LimSup_SalControl(void * self){
  struct ControlPID * _cont = self;
  return MAX_VALUE_SALIDA_CONTROL; 
}

const char * const strsSalcont[3]={
      "cAL ",									
			"rEF ",
			"MAn "
};

char * PID_getSalContTxt(uchar num_txt){
  return strsSalcont[num_txt];
}

/*
** ===================================================================
**     Method      :  get_H_Control 
**     Description :  Histeresis
** ===================================================================
*/
int get_H_Control(void * self){
  struct ControlPID * _cont = self;
  return  (get_TipoControl(_cont)==CNTR_ONOFF)?-_cont->_conf->iHisteresis:_cont->_conf->iHisteresis;  
}

byte set_H_Control(void * self,int val){
  struct ControlPID * _cont = self;
  byte err;  
  err=EscribirWord((word)& _cont->_conf->iHisteresis,abs(val));
  
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
  struct ControlPID * _cont = self;
  return _cont->_conf->iIntegral;
}

byte set_integral(void * self,int val){
  struct ControlPID * _cont = self;
  byte err= EscribirWord((word)&_cont->_conf->iIntegral,val);
  return err;
}

int get_LimSup_integral(void){
  return MAX_INTEGRAL;
}

/*
** ===================================================================
**     Method      :  get_derivada 
**     Description :  Constante de derivacion
** ===================================================================
*/
int get_derivada(void * self){
  struct ControlPID * _cont = self;
  return _cont->_conf->iDerivada;
}

byte set_derivada(void * self,int val){
  struct ControlPID * _cont = self;
  byte err= EscribirWord((word)&_cont->_conf->iDerivada,val);
  return err;
}

int get_LimSup_derivada(void){
  return MAX_DERIVADA;
}

/*
** ===================================================================
**     Method      :  get_PotenciaInf 
**     Description :  Limite Inferior de Potencia de Salida
** ===================================================================
*/
int get_PotenciaInf(void * self){
  struct ControlPID * _cont = self;
  return _cont->_conf->iPotenciaInf;
}

byte set_PotenciaInf(void * self,int val){
  struct ControlPID * _cont = self;
  return EscribirWord((word)&_cont->_conf->iPotenciaInf,val);
}

int get_LimInf_PotenciaInf(void){
  return MIN_POTENCIA;
}
int get_LimSup_PotenciaInf(void * self){
  struct ControlPID * _cont = self;
  return _cont->_conf->iPotenciaSup;
}

/*
** ===================================================================
**     Method      :  get_PotenciaSup 
**     Description :  Limite Superior de Potencia de Salida
** ===================================================================
*/
int get_PotenciaSup(void * self){
  struct ControlPID * _cont = self;
  return _cont->_conf->iPotenciaSup;
}

byte set_PotenciaSup(void * self,int val){
  struct ControlPID * _cont = self;
  return EscribirWord((word)&_cont->_conf->iPotenciaSup,val);
}

int get_LimInf_PotenciaSup(void * self){
  struct ControlPID * _cont = self;
  return _cont->_conf->iPotenciaInf;
}
int get_LimSup_PotenciaSup(void){
  return MAX_POTENCIA;
}
/*
** ===================================================================
**     Method      :  get_PotenciaManual 
**     Description :  Valor de la Potencia de Salida en Manual
** ===================================================================
*/
int get_PotenciaManual(void * self){
  struct ControlPID * _cont = self;
  return _cont->_conf->iPotenciaManual;
}

byte set_PotenciaManual(void * self,int val){
  struct ControlPID * _cont = self;
  return EscribirWord((word)&_cont->_conf->iPotenciaManual,val);
}

int get_LimInf_PotenciaManual(void * self){
  struct ControlPID * _cont = self;
  return _cont->_conf->iPotenciaInf;
}
int get_LimSup_PotenciaManual(void * self){
  struct ControlPID * _cont = self;
  return _cont->_conf->iPotenciaSup;
}
 