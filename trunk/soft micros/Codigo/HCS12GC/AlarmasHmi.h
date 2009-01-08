#ifndef _ALARMAS_HMI
#define _ALARMAS_HMI

/*
** ===================================================================
**     Function    :  AlarmasHmi_AddBoxes 
**     Description :  Agrega la alarma a los boxes 
** ===================================================================
*/
void AlarmasHmi_AddBoxes(const struct AlarmaMult * al,uchar num_obj);
/*
** ===================================================================
**     Function      :  AlarmasHmi_ComuAdd 
**     Description :  Agrega la alarma a la comunicacion
** ===================================================================
*/
word AlarmasHmi_ComuAdd(const struct AlarmaMult * al,word dir_ini);
 
#endif 