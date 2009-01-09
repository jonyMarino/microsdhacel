#ifndef _CONTROL_CC_H
#define _CONTROL_CC_H

#include "Control.h"

typedef enum{
  S_5,
  S_10,
  S_15,
  S_20
}T_Tiempos_Colada;

#define MAX_VALUE_TIEMPO_COLADA 3


#define RAMP_TO_SP_REFERSH_TIME 1000	 // Tiempo en el que se actualiza el SP

#undef CNTR_OnInit
void CC_OnInit(int (*pf_getValProc) (byte));

#undef CNTR_ActProcVal
void CC_ActProcesValue(int vp, byte result,byte chan);

#undef DutyControl 
void CC_DutyControl(int * duty,byte chan);

int CC_getPotenciaSup(byte num_cont);

bool CC_isSoftStart(byte num_cont);

/*  Configuracion */

/*  Limite Superior de Potencia de Salida en Soft Start */
int CC_getPotencia(byte num_cont);
byte CC_setPotencia(int val,byte num_cont);
int CC_getLimInfPotencia(byte num_cont);
int CC_getLimSupPotencia(void);

/*  Constante que indica el corte en Soft Start */
int CC_getConstanteCorte(byte num_cont);
byte CC_setConstanteCorte(int val,byte num_cont);
int CC_getLimInfConstanteCorte(byte num_cont);
int CC_getLimSupConstanteCorte(void);

/*  Tiempo en Soft Start  en caso de constante 0*/
int CC_getTiempoColada(byte num_cont);
byte CC_setTiempoColada(int val,byte num_cont);
int CC_getLimInfTiempoColada(byte num_cont);
int CC_getLimSupTiempoColada(void);
/*  Ciclo en Segundos de Potencia Critica y Potencia de Relajo*/
int CC_getCicleTime(byte num_cont);
byte CC_setCicleTime(int val,byte num_cont);
int CC_getLimInfCicleTime(byte num_cont);
int CC_getLimSupCicleTime(void);
/* Tiempo en Segundos en que se puede estar en potencia critica*/
int CC_getCriticalPotTime(byte num_cont);
byte CC_setCriticalPotTime(int val,byte num_cont);
int CC_getLimInfCriticalPotTime(byte num_cont);
int CC_getLimSupCriticalPotTime(byte num_cont);
/*  Limite Inferior de Potencia Critica */
int CC_getCriticalPot(byte num_cont);
byte CC_setCriticalPot(int val,byte num_cont);
int CC_getLimInfCriticalPot(byte num_cont);
int CC_getLimSupCriticalPot(byte num_cont);
/*  Limite Superior de la Potencia de Relajo */
int CC_getRelaxPot(byte num_cont);
byte CC_setRelaxPot(int val,byte num_cont);
int CC_getLimInfRelaxPot(byte num_cont);
int CC_getLimSupRelaxPot(byte num_cont);


#endif