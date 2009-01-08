#include "cnfbox.h"
#include "boxes.h"
#include "friend_parametros.h"
#include "ControlCC.h"
#include "friend_boxes_cc.h"

#ifdef _COLADA_CALIENTE

const Numerico1 Box_CC_Const;
const Textual1 Box_TiempoCC;
const NumericoJumpCond Box_CC_PotCicle;
const Numerico1 Box_TiempoCritPot;
const Numerico1 Box_PotCritica;
const Numerico1 Box_PotRelax;

const Numerico1 Box_CCPot={
      ProcNumerico1,									                      /* funcion que procesa al box*/
			"P 2 ",							                              /* texto del titulo */
      &ParCC_Pot,					                        /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			1,
			1,											                          //pos punto dec
  	  (PunteroF)&Box_CC_Const						  //Proximos estados
			};


const Numerico1 Box_CC_Const={
      ProcNumerico1,									                      /* funcion que procesa al box*/
			"Crt ",							                              /* texto del titulo */
      &ParCC_Const,					                        /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			1,
			3,											                          //pos punto dec
  	  (PunteroF)&Box_TiempoCC						  //Proximos estados
};


const char * const strs_TiempoCC[]={
      "S-5 ",									
			"S-10",
			"S-15",
			"S-20",
};


const Textual1 Box_TiempoCC=
      {ProcTextual1,						         /* funcion que procesa al box*/
			"tie ",									         //nombre display
			&ParCC_TiempoSS,							 /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			1,
			strs_TiempoCC,                        // Array donde estan los textos
			(PunteroF)&Box_CC_PotCicle				//enter rap,enter mant			
 			};
 			
 			
PunteroF siguiente_box_cicloCC(byte tecla){
  if(tecla=='r'){
    if(CC_getCicleTime(0)!=0)
      return (PunteroF)&Box_TiempoCritPot;
    return (PunteroF)&Principal1;
  }return NULL;
}

const NumericoJumpCond Box_CC_PotCicle={
      ProcNumJumpCond,									                      /* funcion que procesa al box*/
			"CicL",							                              /* texto del titulo */
      &ParCC_PotCicle,					                        /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			1,
			0,											                          //pos punto dec
  	  siguiente_box_cicloCC						  //Proximos estados
};

const Numerico1 Box_TiempoCritPot={
      ProcNumerico1,									                      /* funcion que procesa al box*/
			"t.cri",							                              /* texto del titulo */
      &ParCC_CritPotTime,					                        /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			1,
			0,											                          //pos punto dec
  	  (PunteroF)&Box_PotCritica						  //Proximos estados
};


const Numerico1 Box_PotCritica={
      ProcNumerico1,									                      /* funcion que procesa al box*/
			"P.cri",							                              /* texto del titulo */
      &ParCC_CritPot,					                        /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			1,
			1,											                          //pos punto dec
  	  (PunteroF)&Box_PotRelax						  //Proximos estados
};

const Numerico1 Box_PotRelax={
      ProcNumerico1,									                      /* funcion que procesa al box*/
			"P.rEL",							                              /* texto del titulo */
      &ParCC_RelaxPot,					                        /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			1,
			1,											                          //pos punto dec
  	  (PunteroF)&Principal1						  //Proximos estados
};

#endif
