/* PARAMETROS de calibracion */
/*****************************/

#include "Mydefines.h"
#include "cnfbox.h"
#include "Programador.h"
#include "PE_Types.h"
#include "Sensores.h"
#include "boxescal.h"
#include "friend_parametros.h"

#ifdef _BUTTON_CHANEL_HMI 
#include "boxes_HMI2.h"
#endif
#include "boxes.h"


#pragma CONST_SEG DEFAULT 
#pragma STRING_SEG DEFAULT

const Textual1 TipoSensor1;
const Numerico1 Offset1;
const Numerico2 Ganancia1;
//const Textual Filtro1;
const Numerico1 Filtro1;

#if  CANTIDAD_CANALES>1
const Textual1 TipoSensor2;
const Numerico1 Offset2;
const Numerico2 Ganancia2;
#endif

const Numerico1 ACT1;
const Numerico1 AGT1;
const Numerico1 ATA1;
const Numerico1 ACP1;
const Numerico1 AGP1;
const Numerico1 AAnlLow1;
const Numerico1 AAnlHi1;

#if  CANTIDAD_CANALES>1
const Numerico1 ACT2;
const Numerico1 AGT2;
const Numerico1 ACP2;
const Numerico1 AGP2;
#endif


 /*ajuste minimo Retransmision*/		
const Numerico1 AAnlLow1={
      ProcNumerico1,									/* funcion que procesa al box*/
			"AnL1",							/* texto del titulo */
      &ParRetLow,													/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			CANTIDAD_CANALES,
			1,													/* punto decimal a enc */
			(PunteroF)&AAnlHi1						//Proximos estados
			};			

/*ajuste maximo Retransmision*/		
const Numerico1 AAnlHi1={
      ProcNumerico1,									/* funcion que procesa al box*/
			"AnH1",							/* texto del titulo */
      &ParRetHi,													/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			CANTIDAD_CANALES,
			1,													/* punto decimal a enc */
			(PunteroF)&ATA1						//Proximos estados
			};	
			
  

 
