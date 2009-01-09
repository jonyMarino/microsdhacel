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

#include "com_events.h"

#include "ControlPID2SP.h"

#include "PidHmi.h"
#include "Pid2SPHmi.h"

/*****************************/
/********PROPIEDADES**********/
/*****************************/


  /*SP*/
  const struct ConstPropNumPV ParSP2={
    &PropiedadGenerica,PID2SP_getConfSP2,PID2SP_setSP2, PID_getLimInfSP, PID_getLimSupSP,&PropNumPV,"SPA",PID_getDec
  };
  
  const struct ClassPropiedad *const Pid2SPProps[]={
    &ParSP2,
  };
  

/*
** ===================================================================
**     Function      :  Pid2SPHmi_ComuAdd 
**     Description :  Agrega el PID a la comunicacion
** ===================================================================
*/

word Pid2SPHmi_ComuAdd(const struct ControlPID2SP * pid,word dir_ini){
  word cant = sizeof(Pid2SPProps)/sizeof(struct ClassPropiedad *)-1;
  com_Add(Pid2SPProps,pid,dir_ini,dir_ini+cant);
  return cant;
}
  
  
  
 /***********************/
 /****** BOXES  *********/
 /***********************/
 const struct BlockConstBoxPropCond CBox_PID2SP_SP2;
/*
** ===================================================================
**     Function    :  PidHmi_AddBoxes 
**     Description :  Agrega a los boxes el pid
** ===================================================================
*/

 void Pid2SPHmi_AddBoxes(const struct ControlPID2SP * pid,uchar num_obj){
   PidHmi_AddBoxes((const struct ControlPID *) pid,num_obj);
  DN_AddBox(0,"op",&CBox_PID2SP_SP2,pid,num_obj);
 }
 
 /*******************OPERADOR********************************/



/*SP*/

const struct BlockConstBoxPropCond CBox_PID2SP_SP2={
  &BoxPropCond,
  &ParSP2,
  NULL,
  Pid_SPAppear  
};
