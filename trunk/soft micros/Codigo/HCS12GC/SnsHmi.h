#ifndef _SNS_HMI_H
#define _SNS_HMI_H

#include "Array.h"

extern const struct BlockCnstrBoxLin CBox_Sen1;
extern const struct Array arraySenGetters;

#define SNS_HMI_FST_BOX CBox_Sen1

#define SNS_GETTERS_ARRAY arraySenGetters

/*
** ===================================================================
**     Function      :  SnsHmi_ComuAdd 
**     Description :  Agrega el sensor a la comunicacion
** ===================================================================
*/

word SnsHmi_ComuAdd(const struct TSensor_TermoPT * sensor,word dir_ini);
/*
** ===================================================================
**     Function      :  SnsHmi_Add 
**     Description :  Agrega a los boxes el sensor
** ===================================================================
*/

 void SnsHmi_Add(const struct TSensor_TermoPT * sensor,uchar num_obj);
 
 
 #endif