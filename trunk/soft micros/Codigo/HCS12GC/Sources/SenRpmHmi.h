#ifndef _SEN_RPM_HMI_H
#define _SEN_RPM_HMI_H

#include "SensorRPM.h"
/*
** ===================================================================
**     Function      :  SnsHmi_ComuAdd 
**     Description :  Agrega el sensor a la comunicacion
** ===================================================================
*/

word SenRpmHmi_ComuAdd(const struct SensorRpm * sensor,word dir_ini);
/*
** ===================================================================
**     Function      :  SnsHmi_Add 
**     Description :  Agrega a los boxes el sensor
** ===================================================================
*/

 void SenRpmHmi_Add(const struct SensorRpm * sensor,uchar num_obj);
 
 
 #endif