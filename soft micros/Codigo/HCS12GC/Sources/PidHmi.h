#ifndef PID_HMI_H
#define PID_HMI_H


extern const struct Array arrayPidGetters;
#define PID_GETTERS_ARRAY arrayPidGetters
/*
** ===================================================================
**     Function      :  PidHmi_ComuAdd 
**     Description :  Agrega el PID a la comunicacion
** ===================================================================
*/

word PidHmi_ComuAdd(const struct ControlPID * pid,word dir_ini);
/*
** ===================================================================
**     Function    :  PidHmi_AddBoxes 
**     Description :  Agrega a los boxes el pid
** ===================================================================
*/

 void PidHmi_AddBoxes(const struct ControlPID * pid,uchar num_obj);

 uchar Pid_SPAppear(void * pid);

/*
** ===================================================================
**     Macro    :  PidHmi_AddBoxes 
**     Description :  Agrega a los boxes el pid
** ===================================================================
*/
extern const struct BlockConstrUpBox	 CBox_PIDPotencia;
extern const struct BlockConstBoxPropCond CBox_PID_SP;
extern const struct BlockCnstrBoxLin CBox_PID_Lim; 
extern const struct BlockConstBoxPropVarName CBox_PID_Histeresis;
extern const struct BlockConstBoxPropBase CBox_PID_TSalCont;
extern const struct BlockConstBoxPropBase CBox_Reset;

//OP
#define PID_HMI_FST_OP_BOX  CBox_PIDPotencia
#define PID_HMI_SCND_OP_BOX  CBox_PID_SP
//TUN
#define PID_HMI_FST_TUN_BOX  CBox_Reset
#define PID_HMI_SCND_TUN_BOX  CBox_PID_Histeresis
//SET
#define PID_HMI_FST_SET_BOX CBox_PID_TSalCont
//LIM
#define PID_HMI_FST_LIM_BOX CBox_PID_Lim
 
#endif