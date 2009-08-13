/* MODULE: PidHmi.c*/
#include "PropWithInc.h"
#include "PropNumerica.h"
#include "PropNumPV.h"
#include "PropTextual.h"
#include "UpdatedBox.h"

#include "DiagramaNavegacion.h"
#include "ClassBoxLineal.h"
#include "BoxProp.h"
#include "BoxCondicional.h"
#include "BoxPropCond.h"
#include "BoxPropVarName.h"
#include "BoxGetCond.h"
#include "DataBox.h"
#include "sensor_adapt_val.h"

#include "com_events.h"

#include "ControlPID.h"

#include "PidHmi.h"


/*****************************/
/********PROPIEDADES**********/
/*****************************/

  
  int ControlVista_getHisteresis(const void * control){
    int h=get_H_Control(control);  
    return adaptValOut(PID_getSensor(control),h);
  }
  
  byte ControlVista_setHisteresis(const void * control,int h){     
    return set_H_Control(control,adaptValIn(PID_getSensor(control),h));
  }  
  
  /*Histeresis*/
  const struct ConstPropNumPV ParH={
    (const struct Class * const)&PropiedadGenerica,ControlVista_getHisteresis,ControlVista_setHisteresis , getLimInfSensorControl, getLimSupSensorControl,&PropNumPV,"H  ",PID_getDec
  };
  
  

  /* Potencia Actual */
  const struct ConstrGetterNum GetterPIDPot={
    (const struct Class * const)(const struct Class * const)&GetterGenerico,PID_getDuty,&GetterNum,"Pot",1
  };
  
  /*SP*/
  
  int ControlVista_getSP(const void * control){
    int val=PID_getConfSP(control);  
    return adaptValOut(PID_getSensor(control),val);
  }
  
  byte ControlVista_setSP(const void * control,int val){     
    return PID_setConfSP(control,adaptValIn(PID_getSensor(control),val));
  }   

  
  const struct ConstPropNumPV ParSP={
    (const struct Class * const)&PropiedadGenerica,ControlVista_getSP,ControlVista_setSP, PID_getLimInfSP, PID_getLimSupSP,&PropNumPV,"SP ",PID_getDec
  };
  
  
  /*Limite Inferior del SetPoint*/
  const struct ConstPropNumPV ParLimInfSP={
    (const struct Class * const)&PropiedadGenerica,PID_getLimInfSP,set_LimInf_SP,getLimInfSensorControl, getLimSupSensorControl,&PropNumPV,"Li ",PID_getDec
  }; 

  /*Limite Superior del SetPoint*/
  const struct ConstPropNumPV ParLimSupSP={
    (const struct Class * const)&PropiedadGenerica,PID_getLimSupSP,set_LimSup_SP,get_LimInf_LimSupSP,get_LimSup_LimSupSP,&PropNumPV,"LS ",PID_getDec
  }; 

  /*Reset*/
    int ControlVista_getReset(const void * control){
    int val=get_Reset(control);  
    return adaptValOut(PID_getSensor(control),val);
  }
  
  byte ControlVista_setReset(const void * control,int val){     
    return set_Reset(control,adaptValIn(PID_getSensor(control),val));
  } 
  
  const struct ConstPropNumPV ParReset={
    (const struct Class * const)&PropiedadGenerica,ControlVista_getReset,ControlVista_setReset,NULL,NULL,&PropNumPV,"rES",PID_getDec
  };
  
  /*Integral*/
  const struct ConstructorPropWInc ParIntegral={
    (const struct Class * const)&PropiedadGenerica,get_integral,set_integral,get_0,get_LimSup_integral,&PropWInc,"in "
  };

  /*Derivada*/
  const struct ConstructorPropWInc ParDerivada={
    (const struct Class * const)&PropiedadGenerica,get_derivada,set_derivada,get_0,get_LimSup_derivada,&PropWInc,"dr "
  };
  
  /*LimPotInf1*/
  const struct ConstPropNum ParLimPotInf={
    (const struct Class * const)&PropiedadGenerica,get_PotenciaInf,set_PotenciaInf,get_LimInf_PotenciaInf,get_LimSup_PotenciaInf,&PropNum,"Pi ",1
  };

  /*LimPotSup*/
  const struct ConstPropNum ParLimPotSup={
    (const struct Class * const)&PropiedadGenerica,get_PotenciaSup,set_PotenciaSup,get_LimInf_PotenciaSup,get_LimSup_PotenciaSup,&PropNum,"PS ",1
  };

  
  /*Tsalcont*/
  const char * const strsSalcont[3]={
        #ifdef _RPM
        "drct.",									
  			"InV. ",
  			#else
        "cAL ",									
  			"rEF ",  			
  			#endif
  			"MAn "
  };

  char * PID_getSalContTxt(uchar num_txt){
    return strsSalcont[num_txt];
  }
  const struct ConstPropTxt ParTipoSalControl={
    (const struct Class * const)&PropiedadGenerica,get_SalControl,set_SalControl,get_0,get_LimSup_SalControl,&PropTxt,"C  ",PID_getSalContTxt
  };

  /*Potencia*/
  const struct ConstPropNum ParPotencia={
    (const struct Class * const)&PropiedadGenerica,get_PotenciaManual,set_PotenciaManual,get_LimInf_PotenciaManual,get_LimSup_PotenciaManual,&PropNum,"Pot",1
  };

  const void *const PidProps[]={
    &ParH,
    &ParSP,
    &ParLimInfSP,
    &ParLimSupSP,
    &ParIntegral,
    &ParDerivada,
    &ParLimPotInf,
    &ParLimPotSup,
    &ParTipoSalControl,
    &ParPotencia,
    &ParReset
  };
  
  const NEW_ARRAY(arrayPidGetters,PidProps);
  

/*
** ===================================================================
**     Function      :  PidHmi_ComuAdd 
**     Description :  Agrega el PID a la comunicacion
** ===================================================================
*/

word PidHmi_ComuAdd(const struct ControlPID * pid,word dir_ini){
  word cant = sizeof(PidProps)/sizeof(struct ClassPropiedad *)-1;
  com_Add(PidProps,pid,dir_ini,dir_ini+cant);
  return cant;
}
  
  
  
 /***********************/
 /****** BOXES  *********/
 /***********************/
extern const struct BlockConstrUpdatedBox	 CBox_PIDPotencia;
extern const struct BlockConstBoxPropCond CBox_PID_SP;
extern const struct BlockCnstrBoxLin CBox_PID_Lim; 
extern const struct BlockConstBoxPropVarName CBox_PID_Histeresis;
extern const struct BlockConstBoxPropBase CBox_PID_TSalCont;
extern const struct BlockConstBoxPropBase CBox_Reset;
 
extern const struct BlockConstBoxPropCond CBox_PID_Pot;
extern const struct BlockCnstrBoxLin CBox_PID_Tun; 
/*
** ===================================================================
**     Function    :  PidHmi_AddBoxes 
**     Description :  Agrega a los boxes el pid
** ===================================================================
*/

 void PidHmi_AddBoxes(const struct ControlPID * pid,uchar num_obj){
  DN_AddBox(0,"op",&CBox_PIDPotencia,pid,num_obj);
  DN_AddBox(0,"op",&CBox_PID_SP,pid,num_obj);			
  DN_AddBox(0,"tun ",&CBox_Reset,pid,num_obj);
  DN_AddBox(0,"tun ",&CBox_PID_Histeresis,pid,num_obj);
  DN_AddBox(0,"Set ",&CBox_PID_TSalCont,pid,num_obj);
  DN_AddBox(0,"Lim ",&CBox_PID_Lim,pid,num_obj);
 }
 
 /*******************OPERADOR********************************/

uchar Pid_SPAppear(void * pid){
  const struct ControlPID * _pid = (const struct ControlPID *)pid;
  if(_pid->_conf->eSalidaControl==_MAN)
    return FALSE;
  return TRUE;
}

/* Potencia */

const struct BlockConstrUpBox	 CBox_PIDPotencia={
  &UpdatedBox,
  &GetterPIDPot,
  500,
};


/*SP*/

const struct BlockConstBoxPropCond CBox_PID_SP={
  &BoxPropCond,
  (struct ConstructorPropWInc*)&ParSP,
  &CBox_PID_Pot,
  Pid_SPAppear  
};
/*Potencia*/
uchar Pid_PotAppear(void * pid){
  return !Pid_SPAppear(pid);
}

const struct BlockConstBoxPropCond CBox_PID_Pot={
      &BoxPropCond,
      (struct ConstructorPropWInc*)&ParPotencia,
      NULL,
			Pid_PotAppear
};

/*********************LIM************************************/
  
const struct ConstructorPropWInc*const Props_PID_Lim[]=	{
  			  (struct ConstructorPropWInc*)&ParLimInfSP,											/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
  			  (struct ConstructorPropWInc*)&ParLimSupSP,
  			  (struct ConstructorPropWInc*)&ParLimPotInf,
  			  (struct ConstructorPropWInc*)&ParLimPotSup,
  			  NULL
};

const struct BlockCnstrBoxLin CBox_PID_Lim={
      &BoxLineal,
      Props_PID_Lim,
			NULL
			};
			
			
/*********************TUN************************************/ 

/* Periodo */
const struct BlockConstBoxPropBase CBox_Reset={
      &BoxPropBase,									/* funcion que procesa al box*/
      (struct ConstructorPropWInc*)&ParReset												
};

char * PID_getHDesc(struct PropWInc * prop){
  if(PropWInc_getValorTmp(prop)>0)
    return "Ab";
  return "H";
}

const struct BlockConstBoxPropVarName CBox_PID_Histeresis={
  &BoxPropVarName,
  (struct ConstructorPropWInc*)&ParH,
  &CBox_PID_Tun,
  PID_getHDesc  
};
  
/* limite inferior del set-point de control principal*/ 

const struct ConstructorPropWInc*const Props_PID_Tun[]=	{										
  			  (struct ConstructorPropWInc*)&ParIntegral,
  			  (struct ConstructorPropWInc*)&ParDerivada,
  			  NULL
};

const struct BlockCnstrBoxLin CBox_PID_Tun={
      &BoxLineal,
      Props_PID_Tun,
			NULL
			};


/**************************SET************************************************************************/

/*Modo Salida*/		
const struct BlockConstBoxPropBase CBox_PID_TSalCont=
      {
      &BoxPropBase,						                  /* funcion que procesa al box*/
			(struct ConstructorPropWInc*)&ParTipoSalControl											/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			};




	
  