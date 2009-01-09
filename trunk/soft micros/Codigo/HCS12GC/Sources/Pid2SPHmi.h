#ifndef PID2SP_HMI_H
#define PID2SP_HMI_H

/*
** ===================================================================
**     Function      :  Pid2SPHmi_ComuAdd 
**     Description :  Agrega el PID a la comunicacion
** ===================================================================
*/

word Pid2SPHmi_ComuAdd(const struct ControlPID2SP * pid,word dir_ini);
/*
** ===================================================================
**     Function    :  Pid2SPHmi_AddBoxes 
**     Description :  Agrega a los boxes el pid
** ===================================================================
*/

 void Pid2SPHmi_AddBoxes(const struct ControlPID2SP * pid,uchar num_obj);


#endif