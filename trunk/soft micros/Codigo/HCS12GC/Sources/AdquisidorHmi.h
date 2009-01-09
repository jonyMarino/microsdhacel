#ifndef _ADQUISIDOR_HMI_H
#define _ADQUISIDOR_HMI_H

#include "Adquisidor.h"

extern const struct BlockCnstrBoxLin CBox_Adq1;

#define ADQ_FST_BOX CBox_Adq1


extern const struct Array arrayAdqGetters;
#define ADQ_GETTERS_ARRAY arrayAdqGetters
/*
** ===================================================================
**     Function      :  AdqHmi_ComuAdd 
**     Description :  Agrega el adquisidor a la comunicacion
** ===================================================================
*/

word AdqHmi_ComuAdd(const struct Adquisidor * adq,word dir_ini);
/*
** ===================================================================
**     Function    :  AdqHmi_AddBoxes 
**     Description :  Agrega a los boxes el aquisidor
** ===================================================================
*/
void AdqHmi_AddBoxes(const struct Adquisidor * pid,uchar num_obj);

#endif 