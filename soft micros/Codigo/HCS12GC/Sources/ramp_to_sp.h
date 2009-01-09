#ifndef _RAMP_TO_SP_H
#define _RAMP_TO_SP_H

#include "PE_Types.h"

void RMP_Init(void);

///////Velocidad//////////////////
byte RMP_set_Velocity(int val);
int RMP_get_Velocity(void);

///////Set Point//////////////////
byte RMP_set_SetPoint(int val);
int RMP_get_SetPoint(void);

///////Tiempo Meseta//////////////////
byte RMP_set_DwellTime(int val);
int RMP_get_DwellTime(void);

///////Funcion: Esta en Meseta?////////////////
bool RMP_isDwell(void);

/////// Get Tiempo de Meseta corriendo/////////
int get_RunningDwellTime(void);

#endif