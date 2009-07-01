#include <stdlib.h>


#include "funciones.h"
#include "AlarmaDeSensor.h"
#include "IFsh10.h"
#include "SensorTPT_Class.h"
#include "ManejadorMemoria.h"
#include "PWM.h"
#include "sensor_adapt_val.h"

#pragma DATA_SEG AlarmaDeSensor_DATA                                            
#pragma CODE_SEG AlarmaDeSensor_CODE 
#pragma CONST_SEG DEFAULT 

void AlarmaDeSensor_onConversion(void * self);   //procesador de AlarmaDeSensorarma al fin del sensor 

const char * const strsTAlarmaDeSensor1[]={  
  "E   ",
  "d   ",
  "ErEt",
  "drEt",
  "dbLo",
  "rEt "
};

void AlarmaDeSensor_Duty(void * self,int vxalar);
void AlarmaDeSensor_DefConstructor(void * self,va_list * args);
int AlarmaDeSensor_getOP_Al(struct AlarmaDeSensor * _al);

const struct TControlClass AlarmaDeSensorTable={
  CLASS_INITIALIZATION(TControlClass,AlarmaDeSensor,Object,AlarmaDeSensor_DefConstructor,Object_dtor,Object_differ,Object_puto),
  AlarmaDeSensor_setValor
};

const void *const AlarmaDeSensor = &AlarmaDeSensorTable;

extern struct FlashBkpEnFlash flash;
static struct ManejadorDePROM * const pFlash=&flash;
/*
** ===================================================================
**     Method      :  AlarmaDeSensor_constructor 
**     Description :  Constructor de la alarma
** ===================================================================
*/
void AlarmaDeSensor_constructor(void * self,void * _conf,void * sensor,void * salida){
  struct AlarmaDeSensor * _al=self;
  const NEW_METHOD( onSensor, AlarmaDeSensor_onConversion,self);
    
  _al->sensor=sensor;
  _al->salida=salida;
  _al->_conf=_conf;
  
  AlarmaDeSensor_setHisteresis(_al,AlarmaDeSensor_getHisteresis(_al));  

  AlarmaDeSensor_setTipoAlarma(_al,AlarmaDeSensor_getTipoAlarma(_al));
  
  Sensor_addNuevaMedicionListener(sensor,&onSensor);

}

/*
** ===================================================================
**     Method      :  AlarmaDeSensor_DefConstructor 
**     Description :  Constructor por defecto de la alarma
** ===================================================================
*/
void AlarmaDeSensor_DefConstructor(void * self,va_list * args){
  AlarmaDeSensor_constructor(self,va_arg(*args,void*),va_arg(*args,void*),
                  va_arg(*args,void*));  
}


/*
** ===================================================================
**     Method      :  AlarmaDeSensor_manejador 
**     Description :  
** ===================================================================
*/
void AlarmaDeSensor_manejador(void * self, uchar tecla){
 struct AlarmaDeSensor * _al=self;
 
 if(tecla=='k')
  _al->flagalar=FALSE;
 
 
}




/*
** ===================================================================
**     Method      :  AlarmaDeSensor_valorControl 
**     Description :  retorna el valor de control
** ===================================================================
*/
int AlarmaDeSensor_valorControl(void* self){
  struct AlarmaDeSensor * _al=self;
  int vp = _Getter_getVal(_al->sensor); 
  int valor= AlarmaDeSensor_getOP_Al(_al);
  
  return vp-valor;
}

/*
** ===================================================================
**     Method      :  AlarmaDeSensor_onConversion 
**     Description :  
** ===================================================================
*/
void AlarmaDeSensor_onConversion(void * self){
 struct AlarmaDeSensor * _al=self;
 int vxalar;
 
 if(!getConectada(_al->salida))
    return;
 
 
 //Tipo de setpoint de alarma													
 vxalar=AlarmaDeSensor_valorControl(self);
 
   
 AlarmaDeSensor_Duty(_al,vxalar);
 
}


/*
** ===================================================================
**     Method      :  AlarmaDeSensor_tipoSalidaActual 
**     Description :  
** ===================================================================
*/

TipoSalida AlarmaDeSensor_tipoSalidaActual(void * self){
 struct AlarmaDeSensor * _al=self;
 return getTipoSalida(_al->salida);
}


/*
** ===================================================================
**     Method      :  AlarmaDeSensor_getOP_AlarmaDeSensor 
**     Description :  Obtiene el valor de la alarma que se utiliza 
**     para las  OPeraciones de calculo del control
** ===================================================================
*/
int AlarmaDeSensor_getOP_Al(struct AlarmaDeSensor * _al){
  return adaptValOut( _al->sensor, _al->_conf->valor);
}

/*
** ===================================================================
**     Method      :  AlarmaDeSensor_getOP_HA 
**     Description :  Obtiene el valor de la histeresis de alarma que 
**            se utiliza para las  OPeraciones de calculo del control
** ===================================================================
*/
int AlarmaDeSensor_getOP_HA(struct AlarmaDeSensor * _al){
  return adaptValOut( _al->sensor, _al->_conf->histeresis);
}

/*
** ===================================================================
**     Method      :  AlarmaDeSensor_Duty 
**     Description :  Calcula el Duty de salida para la alarma
** ===================================================================
*/
void AlarmaDeSensor_Duty(void * self,int vxalar){
  
  struct AlarmaDeSensor * _al=self;
  int vp = _Getter_getVal(_al->sensor); 
  int valor= AlarmaDeSensor_getOP_Al(_al);
  int ha= AlarmaDeSensor_getOP_HA(_al);  
  int dutytmp;

//Tipo de salida de alarma 1 aparato viejo
 switch (_al->_conf->tipoAlarma){				
														
    case AL_EXCESO:														
      if(AlarmaDeSensor_tipoSalidaActual(_al)==SALIDA_ONOFF)
      {
        dutytmp = duty_onoff(vxalar, 	          //variable
                             ha 	          //histeresis
                             );	                //valor del duty 
                             
        if(dutytmp<0) //no cambio
          return; 
      } 
      else dutytmp = duty_prop(vxalar, 	          //setpoint
                          ha,
                          0,                  //pot inf
                          1000                //pot sup
                          );
    break;    

    case AL_DEFECTO:														
    if(!AlarmaDeSensor_tipoSalidaActual(_al)){
       dutytmp = duty_onoff(
                         vxalar, 	          //variable
                         ha 	          //histeresis
                         );	                //valor del duty 
       if(dutytmp<0)  //no cambio
        return; 
       dutytmp = 1000-dutytmp; 
    }
    else {
       dutytmp = duty_prop(vxalar, 	        //setpoint
                        ha,
                        0,                  //pot inf
                        1000                //pot sup
                        );
       dutytmp = 1000-dutytmp;
    }
    break;

    case _eret:														

       if(_al->flagalar==FALSE)
       dutytmp = duty_onoff(
                            vxalar, 	          //variable
                            ha	  //histeresis
                            );	                //valor del duty 
       if(dutytmp<0)  //no cambio
        return;                     
       if(dutytmp==1000)
		    _al->flagalar = TRUE;
    break;

    case _dret:														

       if(_al->flagalar==1){
         dutytmp = duty_onoff(
                           vxalar, 	                //variable
                           ha 	  //histeresis
                           );	
         if(dutytmp<0)	 //recupero
          return;                                     
         dutytmp = 1000-dutytmp; 
       }

       if(dutytmp==1000)
		    _al->flagalar = TRUE;
    break;

    case _dbloq:														
       dutytmp = duty_onoff(
                         vxalar, 	                //variable
                         ha 	  //histeresis
                         );	                      //valor del duty 
       if(dutytmp<0)	 //recupero
          return; 
       dutytmp = 1000-dutytmp; 

       if(dutytmp==0)
		      _al->flagalar = TRUE;  
       else if(_al->flagalar == FALSE)
        dutytmp=0;
    break;

    case _RET:  {
      
       long retValue=((long)(VAlarmaDeSensor_RET - _al->_conf->retLow))*1000/(_al->_conf->retHi-_al->_conf->retLow); 

			 if(retValue>1000)
			  dutytmp=1000;
			 else if(retValue<0)
			  dutytmp=0;
			 else
			  dutytmp=retValue;
			 break;
    }
 };

 setPotenciaSalida(_al->salida,dutytmp);

}




/*
** ===================================================================
**     Method      :  AlarmaDeSensor_SetearOnOff 
**     Description :  Funcion para setear el tipo de salida en on-off,
** ===================================================================
*/
void AlarmaDeSensor_SetearOnOff(void * self,byte TipoControl){
  struct AlarmaDeSensor * _al=self;
  
  if(TipoControl==SALIDA_PROPORCIONAL) 
      setTipoSalida(_al->salida,FALSE);
  else
      setTipoSalida(_al->salida,TRUE);
}

/*
** ===================================================================
**     Method      :  AlarmaDeSensor_setTipoControl 
**     Description :  Obtiene histeresis
** ===================================================================
*/
byte AlarmaDeSensor_setTipoControl(void * self,int val){
  struct AlarmaDeSensor * _al=self;
  return _MANEJADOR_MEMORIA_SET_BYTE(pFlash,&_al->_conf->tipoControl,val);  
}

void AlarmaDeSensor_restaurarOnOff(void * self){
  struct AlarmaDeSensor * _al=self;
  AlarmaDeSensor_SetearOnOff(_al,_al->_conf->tipoControl);
}
/*
** ===================================================================
**     Method      :  AlarmaDeSensor_getHisteresis 
**     Description :  Obtiene histeresis
** ===================================================================
*/
int AlarmaDeSensor_getHisteresis(void * self){
  struct AlarmaDeSensor * _al=self;
  int his=_al->_conf->histeresis;
  
  return (_al->_conf->tipoControl==SALIDA_ONOFF)?-his:his;
}

byte AlarmaDeSensor_setHisteresis(void * self,int val){
byte err;  
  struct AlarmaDeSensor * _al=self;
  err=_MANEJADOR_MEMORIA_SET_WORD(pFlash,&_al->_conf->histeresis,abs(val));
  if(!err){
    err=AlarmaDeSensor_setTipoControl(_al,(val<0)?SALIDA_ONOFF:SALIDA_PROPORCIONAL);
    if( _al->_conf->tipoAlarma!=_RET){
      if(val<0)
        AlarmaDeSensor_SetearOnOff(_al,SALIDA_ONOFF);
      else
        AlarmaDeSensor_SetearOnOff(_al,SALIDA_PROPORCIONAL);  
    }
  }
  return err;
}



/*
** ===================================================================
**     Method      :  AlarmaDeSensor_getValor 
**     Description :  Obtiene el valor de alarma
** ===================================================================
*/
int AlarmaDeSensor_getValor(void * self){
  struct AlarmaDeSensor * _al=self;
  return  _al->_conf->valor;
}

byte AlarmaDeSensor_setValor(void * self,int val){
  struct AlarmaDeSensor * _al=self;
  return _MANEJADOR_MEMORIA_SET_WORD(pFlash,&_al->_conf->valor,val);
}

int AlarmaDeSensor_limInf(void * self){
  struct AlarmaDeSensor * _al=self;
  return _Sensor_getLimInf( _al->sensor);
}

int AlarmaDeSensor_limSup(void * self){
  struct AlarmaDeSensor * _al=self;
  return _Sensor_getLimSup(_al->sensor);
}

uchar AlarmaDeSensor_decimales(void * self){
  struct AlarmaDeSensor * _al=self;
  return _getDec(_al->sensor);  
}


/*
** ===================================================================
**     Method      :  AlarmaDeSensor_getTipoAlarma 
**     Description :  Obtiene el tipo de alarma	 1
** ===================================================================
*/

int AlarmaDeSensor_getTipoAlarma(void * self){
  struct AlarmaDeSensor * _al=self;
  return _MANEJADOR_MEMORIA_GET_BYTE(pFlash,&_al->_conf->tipoAlarma);
}

byte AlarmaDeSensor_setTipoAlarma(void * self,int val){
  struct AlarmaDeSensor * _al=self;
  byte err= _MANEJADOR_MEMORIA_SET_BYTE(pFlash,&_al->_conf->tipoAlarma,val);
  if(!err){
    if(val==_RET){
      AlarmaDeSensor_SetearOnOff(_al,SALIDA_PROPORCIONAL);
      setPeriodo(_al->salida,PWM_Anl);
    }else{     
      AlarmaDeSensor_restaurarOnOff(_al);
      setPeriodo(_al->salida,getPeriodo(_al->salida));
    }
  }
  return err;
}

int AlarmaDeSensor_tipoAlarmaLimSup(void * self){
  struct AlarmaDeSensor * _al=self;
  return TIPO_ALARMA1_LAST;
}			 

char * AlarmaDeSensor_tipoAlarmaMsj(uchar num_str){
  return strsTAlarmaDeSensor1[num_str];
}



/*
** ===================================================================
**     Method      :  AlarmaDeSensor_getRetLow 
**     Description :  Obtiene el valor 0 de retransmision
** ===================================================================
*/
int AlarmaDeSensor_getRetLow(void * self){
  struct AlarmaDeSensor * _al=self;
  return _al->_conf->retLow;
}

byte AlarmaDeSensor_setRetLow(void*self,int val){
  struct AlarmaDeSensor * _al=self;
  return _MANEJADOR_MEMORIA_SET_WORD(pFlash,&_al->_conf->retLow,val);
}

int AlarmaDeSensor_retLowLimSup(void*self){
  struct AlarmaDeSensor * _al=self;
  return _al->_conf->retHi;
}

/*
** ===================================================================
**     Method      :  AlarmaDeSensor_getRetHi 
**     Description :  Obtiene el valor 100 de retransmision
** ===================================================================
*/
int AlarmaDeSensor_getRetHi(void*self){
  struct AlarmaDeSensor * _al=self;
  return _al->_conf->retHi;
}

byte AlarmaDeSensor_setRetHi(void*self,int val){
  struct AlarmaDeSensor * _al=self;
  return _MANEJADOR_MEMORIA_SET_WORD(pFlash,&_al->_conf->retHi,val);
}

int AlarmaDeSensor_retHiLimInf(void*self){
  struct AlarmaDeSensor * _al=self;
  return _al->_conf->retLow;
}

#pragma CODE_SEG AlarmaDeSensor_CODE 


 