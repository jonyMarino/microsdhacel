#ifndef _ALARMA_DE_SENSOR_HMI_H
#define _ALARMA_DE_SENSOR_HMI_H

/*
** ===================================================================
**     Function    :  AlarmasHmi_AddBoxes 
**     Description :  Agrega la alarma a los boxes 
** ===================================================================
*/
void AlarmaDeSensorHmi_AddBoxes(const void * al,uchar num_obj);
/*
** ===================================================================
**     Function      :  AlarmasHmi_ComuAdd 
**     Description :  Agrega la alarma a la comunicacion
** ===================================================================
*/
word AlarmaDeSensorHmi_ComuAdd(const void * al,word dir_ini);

/*  Macro   */
extern const struct BlockConstBoxPropBase CBox_AlarmaDeSensorVal;
extern const struct BlockConstBoxPropVarName CBox_H_AlarmaDeSensor;
extern const struct BlockConstBoxCondl CBox_TAlarmaDeSensor1;

#define ALARMA_DE_SENSOR_HMI_FST_OP CBox_AlarmaDeSensorVal
#define ALARMA_DE_SENSOR_HMI_FST_TUN CBox_H_AlarmaDeSensor
#define ALARMA_DE_SENSOR_HMI_FST_SET CBox_TAlarmaDeSensor1
 
#endif 