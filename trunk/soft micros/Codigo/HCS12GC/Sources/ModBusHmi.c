/*
**     Filename  : ModBusHmi.C
**     Project   : Controlador
**     Processor : MC9S12GC32CFU
**     Version   : 0.0.1
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 30/01/2008, 11:37
**     Abstract  :
**							Interfaz con la pantalla y la comunicacion
*/

#include "PropWithInc.h"
#include "stddef.h"
#include "modbus.h"

#include "com_events.h"
#include "DiagramaNavegacion.h"
#include "BoxPropBase.h"

#include "ModBusHmi.h"


/*Id*/
const struct ConstructorPropWInc ParId={
    (const struct Class * const)(const struct Class * const)&PropiedadGenerica,get_Id,set_Id,get_0,get_LimSup_Id,&PropWInc,"id"
};

  const void *const modBusGetters[]={
    &ParId,
  };
 
 const NEW_ARRAY(arrayModBusGetters,modBusGetters); 

/*
** ===================================================================
**     Function    :  ModBusHmi_ComuAdd 
**     Description :  Agrega los parametros de comunicacion
**                   a la comunicacion
** ===================================================================
*/

word ModBusHmi_ComuAdd(word dir_ini){
  word cant = sizeof(modBusGetters)/sizeof(struct GetterGenerico *)-1;
  com_Add(modBusGetters,NULL,dir_ini,dir_ini+cant);
  return cant;
}




/**************************SET************************************************************************/

/*Id*/		
const struct BlockConstBoxPropBase CBox_ModBusId=
      {
      &BoxPropBase,						                  /* funcion que procesa al box*/
			&ParId											/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			};


/*
** ===================================================================
**     Function    :  ModBusHmi_AddBoxes 
**     Description :  Agrega a los boxes la comunicacion
** ===================================================================
*/
 void ModBusHmi_AddBoxes(void){
  DN_AddBox(0,"Set ",&CBox_ModBusId,NULL,0);
 }