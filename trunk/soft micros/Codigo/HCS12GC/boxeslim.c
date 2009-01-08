/* PARAMETROS de "Limites" */
/***************************/
#include "Mydefines.h"
#include "cnfbox.h"
#ifdef _BUTTON_CHANEL_HMI 
#include "boxes_HMI2.h"
#endif
#include "boxes.h"

#include "Programador.h"
#include "PE_Types.h"
#include "Sensores.h"
//#include "boxeslim.h"
#include "friend_parametros.h"

#pragma CONST_SEG DEFAULT 
#pragma STRING_SEG DEFAULT

const Numerico1 LimiteInferior1;
const Numerico1 LimiteSuperior1;
const Numerico1 PotenciaInferior1;
const Numerico1 PotenciaSuperior1;

/* limite inferior del set-point de control principal*/ 
const Numerico1 LimiteInferior1={
      ProcNumerico1,
			"Li 1",
      &ParLimInfSP,
			CANTIDAD_SAL_CONTROL,
			DECIMALES_CANAL1,
			(PunteroF)&LimiteSuperior1
			};
			


/* limite superior del set-point de control principal*/  
const Numerico1 LimiteSuperior1={
      ProcNumerico1,
			"LS 1",
      &ParLimSupSP,
			CANTIDAD_SAL_CONTROL,
			DECIMALES_CANAL1,
			(PunteroF)&PotenciaInferior1
			};
						

/* limite inferior de potencia de control principal*/ 
const Numerico1 PotenciaInferior1={
      ProcNumerico1,
			"Pi 1",
      &ParLimPotInf,
			CANTIDAD_SAL_CONTROL,
			1,
			(PunteroF)&PotenciaSuperior1
			};
			
			
/* limite superior de potencia de control principal*/  
const Numerico1 PotenciaSuperior1={
      ProcNumerico1,
			"PS 1",
      &ParLimPotSup,
			CANTIDAD_SAL_CONTROL,
			1,
			(PunteroF)&Principal1
			};
			
