#include <stdlib.h>


#include "funciones.h"
#include "alarmas.h"
#include "IFsh10.h"
#include "SensorTPT_Class.h"

#pragma DATA_SEG ALARMA_CONTROLADOR_DATA                                            
#pragma CODE_SEG ALARMA_CONTROLADOR_CODE 
#pragma CONST_SEG DEFAULT 

void AL_onconvert(void * self);   //procesador de alarma al fin del sensor 

const char * const strsTAL1[]={  
  "E   ",
  "d   ",
  "ErEt",
  "drEt",
  "dbLo",
  "rEt "
};

  
const char * const strsTAL2[]={ 
  "rEL ",
  "AbS ",
  "rEFr",
  "bAn ",
};

void AL_Duty(void * self);
void AL_DefConstructor(void * self,va_list * args);

const struct TControl AlarmaTable={
  sizeof(struct AlarmaMult),
  AL_DefConstructor,
  NULL,
  NULL,
  set_AL
};

const void *const AlarmaMult = &AlarmaTable;


/*
** ===================================================================
**     Method      :  AL_Constructor 
**     Description :  Constructor de la alarma
** ===================================================================
*/
void AL_Constructor(void * self,void * _conf,void * pid,void * salida,int time_desc){
  struct AlarmaMult * _al=self;
    
  _al->pid=pid;
  _al->salida=salida;
  _al->_conf=_conf;
  
  set_H_Alarma(_al,AL_getHisteresis(_al));  

  set_TipoAlarma1(_al,get_TipoAlarma1(_al));

  AL_Disconnect(_al);
  _al->Alartimer= newObj(RlxMTimer,(ulong)time_desc,AL_FstConect,self);  

  _Sensor_AddOnNewVal(PID_getSensor(_al->pid),AL_onconvert,self);

}

/*
** ===================================================================
**     Method      :  AL_DefConstructor 
**     Description :  Constructor por defecto de la alarma
** ===================================================================
*/
void AL_DefConstructor(void * self,va_list * args){
  AL_Constructor(self,va_arg(*args,void*),va_arg(*args,void*),
                  va_arg(*args,void*),va_arg(*args,int));  
}

/*
** ===================================================================
**     Method      :  AL_Disconnect 
**     Description :  Desconecta la salida de la alarma
** ===================================================================
*/
void AL_Disconnect(void * self){
  struct AlarmaMult * _al=self;
  _al->isConnected=FALSE;   
  _Salida_setDuty(_al->salida,0);
}
/*
** ===================================================================
**     Method      :  AL_Connect 
**     Description :  Conecta la salida de la alarma
** ===================================================================
*/
void AL_Connect(void * self){
  struct AlarmaMult * _al=self;
  _al->isConnected=TRUE;
}
/*
** ===================================================================
**     Method      :  AL_FstConect 
**     Description :  Conecta por primera vez la salida de la alarma
** ===================================================================
*/
void AL_FstConect(void * self){
 struct AlarmaMult * _al=self;
 deleteObj(&_al->Alartimer);
 AL_Connect(_al);
}

/*
** ===================================================================
**     Method      :  AL_Handler 
**     Description :  
** ===================================================================
*/
void AL_Handler(void * self, uchar tecla){
 struct AlarmaMult * _al=self;
 
 if(tecla=='k')
  _al->flagalar=FALSE;
 
 
}






 /*
** ===================================================================
**     Method      :  AL_onconvert 
**     Description :  
** ===================================================================
*/
void AL_onconvert(void * self){
 struct AlarmaMult * _al=self;
 
 AL_Duty(_al);
 
}

/*
** ===================================================================
**     Method      :  AL_es_pid 
**     Description :  
** ===================================================================
*/

bool AL_es_pid(void * self){
 struct AlarmaMult * _al=self;
 return _al->TipoControl== CNTR_PID;
}


/*
** ===================================================================
**     Method      :  AL_getOP_AL 
**     Description :  Obtiene el valor de la alarma que se utiliza 
**     para las  OPeraciones de calculo del control
** ===================================================================
*/
int AL_getOP_AL(struct AlarmaMult * _al){
  return _Sensor_AdaptVal(PID_getSensor( _al->pid ), _al->_conf->iAlarma);
}

/*
** ===================================================================
**     Method      :  AL_getOP_HA 
**     Description :  Obtiene el valor de la histeresis de alarma que 
**            se utiliza para las  OPeraciones de calculo del control
** ===================================================================
*/
int AL_getOP_HA(struct AlarmaMult * _al){
  return _Sensor_AdaptVal(PID_getSensor( _al->pid ), _al->_conf->iHistAlarma);
}

/*
** ===================================================================
**     Method      :  AL_Duty 
**     Description :  Calcula el Duty de salida para la alarma
** ===================================================================
*/
void AL_Duty(void * self){
  
  struct AlarmaMult * _al=self;
  const struct Sensor * sensor= PID_getSensor( _al->pid);
  int vp = _Getter_getVal(sensor); 
  int sp = PID_getOP_SP(_al->pid);
  int iAlarma= AL_getOP_AL(_al);
  int ha= AL_getOP_HA(_al);
  int vxalar;  
  int dutytmp;
  
  
  if(!_al->isConnected)
    return;

  
    
//Tipo de setpoint de alarma
  switch (_al->_conf->eTipoAlarma2){				
    case REL:														
          vxalar = vp-(sp+iAlarma);
          break;
 
    case ABS:														
          vxalar = vp-iAlarma;
          break;

//dan!!ver antiwindup

    case REFR:														
          vxalar = -PID_getValControl(_al->pid)-iAlarma;
          break;
          
    case BAN:														
          vxalar = abs(vp-sp)-(iAlarma/2);
          break;    
    default:
			    vxalar = vp-iAlarma;
          break;
  
  
 };

//Tipo de salida de alarma 1 aparato viejo
 switch (_al->_conf->eTipoAlarma1){				
														
    case AL_EXCESO:														
      if(!AL_es_pid(_al))
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
    if(!AL_es_pid(_al)){
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

       if(_al->flagalar==FALSE){
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

    case _RET:
       dutytmp=((long)(VAL_RET - _al->_conf->iRetLow))*1000/(_al->_conf->iRetHi-_al->_conf->iRetLow); 

			 if(dutytmp>1000)
			  dutytmp=1000;
			 else if(dutytmp<0)
			  dutytmp=0;
			 break;
 };

 _Salida_setDuty(_al->salida,dutytmp);

}




/*
** ===================================================================
**     Method      :  AL_SetearOnOff 
**     Description :  Funcion para setear el tipo de salida en on-off,
** ===================================================================
*/
void AL_SetearOnOff(void * self,byte TipoControl){
  struct AlarmaMult * _al=self;

  if(_al->TipoControl==CNTR_PID) 
      _Salida_OnOff(_al->salida,FALSE);
  else
      _Salida_OnOff(_al->salida,TRUE);
}

/*
** ===================================================================
**     Method      :  AL_setTipoControl 
**     Description :  Obtiene histeresis
** ===================================================================
*/
byte AL_setTipoControl(void * self,int val){
  struct AlarmaMult * _al=self;
  return EscribirByte((word)&_al->_conf->tipoControl,val);  
}
/*
** ===================================================================
**     Method      :  AL_getHisteresis 
**     Description :  Obtiene histeresis
** ===================================================================
*/
int AL_getHisteresis(void * self){
  struct AlarmaMult * _al=self;
  int his=_al->_conf->iHistAlarma;
  
  return (_al->_conf->tipoControl==CNTR_ONOFF)?-his:his;
}

byte set_H_Alarma(void * self,int val){
byte err;  
  struct AlarmaMult * _al=self;
  err=EscribirWord((word)&_al->_conf->iHistAlarma,abs(val));
  if(!err){
    err=AL_setTipoControl(_al,(val<0)?CNTR_ONOFF:CNTR_PID);
    if( _al->_conf->eTipoAlarma1!=_RET){
      if(val<0)
        AL_SetearOnOff(_al,CNTR_ONOFF);
      else
        AL_SetearOnOff(_al,CNTR_PID);  
    }
  }
  return err;
}



/*
** ===================================================================
**     Method      :  get_AL 
**     Description :  Obtiene el valor de alarma
** ===================================================================
*/
int get_AL(void * self){
  struct AlarmaMult * _al=self;
  return  _al->_conf->iAlarma;
}

byte set_AL(void * self,int val){
  struct AlarmaMult * _al=self;
  return EscribirWord((word)&_al->_conf->iAlarma,val);
}

int get_LimInf_AL(void * self){
  struct AlarmaMult * _al=self;
  return _Sensor_getLimInf( PID_getSensor(_al->pid));
}

int get_LimSup_AL(void * self){
  struct AlarmaMult * _al=self;
  return _Sensor_getLimSup(PID_getSensor(_al->pid));
}

uchar AL_getDec(void * self){
  struct AlarmaMult * _al=self;
  return _getDec(PID_getSensor(_al->pid));  
}


/*
** ===================================================================
**     Method      :  get_TipoAlarma1 
**     Description :  Obtiene el tipo de alarma	 1
** ===================================================================
*/

int get_TipoAlarma1(void * self){
  struct AlarmaMult * _al=self;
  return _al->_conf->eTipoAlarma1;
}

byte set_TipoAlarma1(void * self,int val){
  struct AlarmaMult * _al=self;
  byte err= EscribirByte((word)&_al->_conf->eTipoAlarma1,val);
  if(!err){
    if(val==_RET)
      PWM_ChangePeriod(_al->salida,PWM_Anl);
    else
      PWM_ChangePeriod(_al->salida,PWM_getPeriod(_al->salida));
  }
  return err;
}

int get_LimSup_TipoAlarma1(void * self){
  struct AlarmaMult * _al=self;
  return TIPO_ALARMA1_LAST;
}			 

char * AL_getTAL1str(uchar num_str){
  return strsTAL1[num_str];
}


/*
** ===================================================================
**     Method      :  get_TipoAlarma1 
**     Description :  Obtiene el tipo de alarma 2
** ===================================================================
*/
int get_TipoAlarma2(void * self){
  struct AlarmaMult * _al=self;
  return _al->_conf->eTipoAlarma2;
}

byte set_TipoAlarma2(void * self,int val){
  struct AlarmaMult * _al=self;
  return EscribirByte((word)&_al->_conf->eTipoAlarma2,val);
}

int get_LimSup_TipoAlarma2(void * self){
  struct AlarmaMult * _al=self;
  return TIPO_ALARMA2_LAST;
}

char * AL_getTAL2str(uchar num_str){
  return strsTAL2[num_str];
}


/*
** ===================================================================
**     Method      :  get_RetLow 
**     Description :  Obtiene el valor 0 de retransmision
** ===================================================================
*/
int get_RetLow(void * self){
  struct AlarmaMult * _al=self;
  return _al->_conf->iRetLow;
}

byte set_RetLow(void*self,int val){
  struct AlarmaMult * _al=self;
  return EscribirWord((word)&_al->_conf->iRetLow,val);
}

int get_LimSup_RetLow(void*self){
  struct AlarmaMult * _al=self;
  return _al->_conf->iRetHi;
}

/*
** ===================================================================
**     Method      :  get_RetHi 
**     Description :  Obtiene el valor 100 de retransmision
** ===================================================================
*/
int get_RetHi(void*self){
  struct AlarmaMult * _al=self;
  return _al->_conf->iRetHi;
}

byte set_RetHi(void*self,int val){
  struct AlarmaMult * _al=self;
  return EscribirWord((word)&_al->_conf->iRetHi,val);
}

int get_LimInf_RetHi(void*self){
  struct AlarmaMult * _al=self;
  return _al->_conf->iRetLow;
}

#pragma CODE_SEG ALARMA_CONTROLADOR_CODE 


 