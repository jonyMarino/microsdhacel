#include "ADC.h"
#include "Mydefines.h"

//valores de las variables simbolicas setpoint1
//#ifndef RPM
#ifdef jony_18_07
#define DELTAT  AD_TIME_EN_MILI_SEGUNDOS      //milisegundos
#else
#define DELTAT 1 
#endif
//#endif
//valores de las variables simbolicas alarma1
#define  t_sp_alarma	 PRom[R_T_AL+NAL]
#define  t_sal_alarma  PRom[R_Talar1+NAL]

#define  vx 					 ValFinal[0+NCN]
#define  valcont 			 ValCont[0+NCN]
#define  dutyold 	 		 duty_alar_ch[NAL]
#define  vxl           ValFinal[0+NCN]
#define  spcont	       SetPoint[0+NCN]

#define  spalar				 PRom[R_AL+NAL]
#define  res 					 PRom[R_Reset+NCN]
#define  hisalar			 PRom[R_HA1+NAL]
#define  abl           PRom[R_H1+NCN]
#define  kint          PRom[R_IN1+NCN]
#define  mdc           PRom[R_Tcontrol1+NCN] 
#define  kdl           PRom[R_DR1+NCN] 

#define  dutyalar			 duty_alar_ch[NAL]

#define  VAL_RET       ValFinal[0]
