#ifndef _SELF_TUNE_H
#define _SELF_TUNE_H

#include "PE_Types.h"

#define St_abrt_MAX 2000000
#define St_abrt_MIN 4000

//#define St_T_MAX 2000000
//#define St_T_MIN 6000
#define St_Hist 2

typedef enum{
  ST_OFF,
  ST_ON,
  ST_AUTO,
  ST_SP
}TSelfTune;
#define ST_MAX_VALUE 3

typedef enum{
  ST_STATE_OFF,
  ST_STATE_RUNNING,
  #ifdef _COLADA_CALIENTE
  ST_STATE_WAIT_SOFT_START,
  #endif
}T_ST_State;

void CST_OnInit( int (*pf_getValProc) (byte));
/*
** ===================================================================
**     Method      :  CST_OnInit
**
**     Description : Inicializa el control con self tune
**     Parameters  : * pf_getValProc - Puntero a funcion para obtener los valores dela variables
**                   num_cntrl  _ Numero de control
**     Returns     : None
**         ---    
** ===================================================================
*/


void CST_DutyControl(int * pduty,byte num_cont);
/*
** ===================================================================
**     Method      :  CST_DutyControl 
**
**     Description : Calcula el duty de salida
**     Parameters  : * pduty - Puntero al duty
**                   num_cntrl  _ Numero de control
**     Returns     : None
**         ---    
** ===================================================================
*/


T_ST_State CST_getState(byte num_cntrl);
// Estado del Self Tune

int get_SelfTun(byte num_ctrl);

byte set_SelfTun(int st,byte num_ctrl);

int get_LimSup_SelfTun(void);


#endif