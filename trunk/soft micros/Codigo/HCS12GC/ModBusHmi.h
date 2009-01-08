/*
**     Filename  : ModBusHmi.h
**     Project   : Controlador
**     Processor : MC9S12GC32CFU
**     Version   : 0.0.1
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 30/01/2008, 11:37
**     Abstract  :
**							Interfaz con la pantalla y la comunicacion
*/
#ifndef _MOD_BUS_HMI_H
#define _MOD_BUS_HMI_H

#include "PE_Types.h"
#include "Array.h"

extern const struct Array arrayModBusGetters; 
#define MODBUS_GETTERS_ARRAY arrayModBusGetters
/*
** ===================================================================
**     Function    :  ModBusHmi_ComuAdd 
**     Description :  Agrega los parametros de comunicacion
**                   a la comunicacion
** ===================================================================
*/
word ModBusHmi_ComuAdd(word dir_ini);

/*
** ===================================================================
**     Function    :  ModBusHmi_AddBoxes 
**     Description :  Agrega a los boxes la comunicacion
** ===================================================================
*/
void ModBusHmi_AddBoxes(void);

/* MACRO  */
extern const struct BlockConstBoxPropBase CBox_ModBusId;

#define MOD_BUS_HMI_FST_BOX_SET CBox_ModBusId 


#endif