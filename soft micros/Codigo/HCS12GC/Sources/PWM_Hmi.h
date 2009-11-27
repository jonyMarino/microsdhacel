#ifndef _PWM_HMI_H
#define _PWM_HMI_H		

#include "PWM.h"

extern const struct Array arrayPWMGetters;
#define PWM_GETTERS_ARRAY arrayPWMGetters

extern const struct Array arrayPWMGetterPot;
#define PWM_GETTER_POT_ARRAY arrayPWMGetterPot

/*
** ===================================================================
**     Function      :  PwmHmi_ComuAdd 
**     Description :  Agrega la salida a la comunicacion
** ===================================================================
*/

word PwmHmi_ComuAdd(const struct PWM * pwm,word dir_ini);

/*
** ===================================================================
**     Function      :  PWM_Hmi_Add 
**     Description :  Agrega a los boxes el pwm
** ===================================================================
*/
void PWM_Hmi_Add(const struct PWM * pwm,uchar num_obj);

void PWMHmi_addIndexedPeriodo(const struct PWM * pwm,uchar access,const char * str,uchar num_obj,uchar index);


//TUN
extern const struct BlockConstBoxPropBase CBox_Periodo;

#define PWM_VISTA_FST_TUN_BOX  CBox_Periodo

extern const struct BlockConstBoxPropBase CBox_PeriodoAL;

#define PWM_AL_VISTA_FST_TUN_BOX  CBox_PeriodoAL

#endif