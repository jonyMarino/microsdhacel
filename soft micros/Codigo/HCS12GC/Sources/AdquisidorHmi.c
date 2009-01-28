/* MODULE: AdquisidorHmi.c*/
#include "PropWithInc.h"
#include "PropNumerica.h"
#include "PropNumPV.h"
#include "PropTextual.h"
#include "PropHora.h"

#include "DiagramaNavegacion.h"
#include "ClassBoxLineal.h"
#include "BoxProp.h"
#include "BoxCondicional.h"
#include "DataBox.h"
#include "ReadOnlyBox.h"

#include "com_events.h"

#include "Adquisidor.h"

#include "AdquisidorHmi.h"

/*****************************/
/********PROPIEDADES**********/
/*****************************/

  /*Actual State*/
  const struct ConstrGetterTxt GetterState={
    &GetterGenerico,Adq_getActualState,&GetterTxt,"StAt",Adq_getStateStr  
  };
  TError  Adq_setStrategy(void * _self, int val);
  /* Strategy*/
  const struct ConstPropTxt ParStrategy={
    &PropiedadGenerica,Adq_getStrategy,Adq_setStrategy, get_0,Adq_LimSupStrategy,&PropTxt,"EStr",Adq_getStrStrategy
  };
  /*Interval*/
  const struct ConstPropHora ParInterval={
    &PropiedadGenerica,Adq_getIntervalo, Adq_setIntervalo, Adq_LimInfIntervalo, NULL,&PropWInc,"intErVALo"
  };
  /*State*/
  const struct ConstPropTxt ParState={
    &PropiedadGenerica,Adq_getState, Adq_SetState, Adq_StateLimInf, Adq_StateLimSup,&PropTxt,"StA1",Adq_getStateStr
  };

  /*Erase Page*/
  int get_1(void * self){
    return 1;
  }
  
  char * AdquisidorHmi_getBorrarStr(int str){
    if(str)
      return "no";
    return "Si";      
  }
  const struct ConstPropTxt ParBorrarPage= {
    &PropiedadGenerica,Adq_getPaginaActual,Adq_ErasePages,get_0,get_1,&PropTxt,"borrAr dAtoS",  
  };
  
  /* Pagina Start*/
  const struct GetterGenerico GetterPagStart={
    &GetterGenerico,Adq_getPaginasStart  
  };
  
  /* Pagina End*/
  const struct GetterGenerico GetterPagEnd={
   &GetterGenerico,Adq_getPaginasEnd 
  };


  const struct GetterGenerico *const AdqProps[]={
    &ParInterval,
    &ParState,
    &ParStrategy,
    &GetterState,
    &GetterState,
    &GetterPagStart,
    &GetterPagEnd    
  };
  
  const NEW_ARRAY(arrayAdqGetters,AdqProps);
/*
** ===================================================================
**     Function      :  AdqHmi_ComuAdd 
**     Description :  Agrega el adquisidor a la comunicacion
** ===================================================================
*/

word AdqHmi_ComuAdd(const struct Adquisidor * adq,word dir_ini){
  word cant = sizeof(AdqProps)/sizeof(struct GetterGenerico *)-1;

  com_Add(AdqProps,adq,dir_ini,dir_ini+cant);

  return cant;
}

const struct BlockConstrReadOnlyBox	 CBox_ActualState;
const struct BlockCnstrBoxLin CBox_Adq1;
/*
** ===================================================================
**     Function    :  AdqHmi_AddBoxes 
**     Description :  Agrega a los boxes el aquisidor
** ===================================================================
*/
void AdqHmi_AddBoxes(const struct Adquisidor * adq,uchar num_obj){
//  DN_AddBox(0,"AdQ",&CBox_ActualState,adq,num_obj);  
  DN_AddBox(0,"AdQ",&CBox_Adq1,adq,num_obj);   
}

/*  Boxes */

/*State*/
const struct BlockConstrReadOnlyBox	 CBox_ActualState={
  &ReadOnlyBox,
  &GetterState
};

/*Group 1*/

const struct ConstructorPropWInc*const Props_Adq[]=	{
  			  &ParInterval,
  			  &ParStrategy,
  			  &ParState,
  			  &ParBorrarPage,
  			  NULL
};

const struct BlockCnstrBoxLin CBox_Adq1={
      &BoxLineal,
      Props_Adq,
			NULL
			};


