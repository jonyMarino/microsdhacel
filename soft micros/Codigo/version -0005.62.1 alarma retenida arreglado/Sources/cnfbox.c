#ifndef _cnfbox_h
#define _cnfbox_h

#include "Mydefines.h"
#include "PE_Types.h"
#include "boxes.h"
#include "boxesprog.h"
#include "boxesadq.h"
#include "boxestun.h"
#include "boxescal.h"
#include "boxesset.h"
#include "cnfbox.h"
#include "Programador.h"
#include "boxescolcal.h"

#include "Sensores.h"
#pragma CONST_SEG DEFAULT 
#pragma STRING_SEG DEFAULT

extern const Textual Ccalstn;

extern const Textual C1STN;
extern const Numerico Vrmp;
extern const Numerico Tmpm;

extern Titulo Colcal;

/* Definicion de las estructuras de los boxes de navegacion */
/************************************************************/
/*		void(*DirTask)(void);		funcion que ejecuta tareas especiales de c/box*/

///VARIABLES EXTERNAS QUE UTILIZAN LOS BOXES //////////////
extern int Estado_Adquisicion;															
extern volatile const int PRom[PARAMETROS];
////Las de Programacion/////////
int Lim_Segmento2[CANTIDAD_SAL_CONTROL];  /* Limite para el segmento que se puede cambiar mientras corre*/
int Lim_TieSeg[CANTIDAD_SAL_CONTROL]; 
/////////////////////////////////
int Lim_Inf_ch[CANTIDAD_CANALES],Lim_Sup_ch[CANTIDAD_CANALES];
int Lim_Dec[CANTIDAD_CANALES];
const int Lim_m9999=-9999;
const int Lim_m1999=-1999;
const int Lim_m1=-1;
const int Lim_0=0;
const int Lim_1=1;
const int Lim_2=2;
const int Lim_3=3;
const int Lim_4=4;
const int Lim_5=5;
const int Lim_6=6;
const int Lim_7=7;
const int Lim_8=8;
const int Lim_9=9;
const int Lim_10=10;
const int Lim_24=24;
//const int Lim_255=255;
const int Lim_255=1000;

const int Lim_600=600;
const int Lim_1000=1000;
const int Lim_9999=9999;
#ifdef jony_28_06
const int Lim_32767=32767;
#endif

#ifdef prog_viejo
const int LimInf_Seg=1;
#else
const int LimInf_Seg=0;
#endif


const int Limite_sensor_Sup=NUM_SENSORES;
#ifdef adquisidor
const int Lim_12 = 12;
const int Lim_2006 = 2006;
const int Lim_2099 = 2099;
#endif


/************************************/
/* Definicion y armado de los boxes */
/************************************/
const Numerico Principal1;

const Numerico C1SP;
const Numerico C1POT;
const Numerico AL1;
const Numerico AL2;
const Numerico AL3;
const Numerico P1;
const Numerico Segmento1;
const Numerico SegundosSegmento1;

#if  CANTIDAD_CANALES>1
const Numerico C2SP;
const Numerico C2POT;
const Numerico C2AL1;
const Numerico P2;
#endif

const Numerico Codigo1;

const Titulo Sintonia;

const Titulo Calibracion;

const Titulo Setting;

const Titulo Limites;

const Numerico LimiteInferior1;
const Numerico LimiteSuperior1;
const Numerico PotenciaInferior1;
const Numerico PotenciaSuperior1;



#if  CANTIDAD_CANALES>1
const Numerico LimiteInferior2;
const Numerico LimiteSuperior2;
const Numerico PotenciaInferior2;
const Numerico PotenciaSuperior2;
#endif

#ifdef programador
const Titulo Programas;
#endif

#ifdef adquisidor
const Titulo Adquisicion;

#endif							

const TDato Parametros[PARAMETROS]={
/*SP1*/{&PRom[R_SetPoint+0], NO_FUNCTION, &PRom[R_Lim_Inf+0], &PRom[R_Lim_Sup+0], CHAN_1},	 //0
/*SP2*/{&PRom[R_SetPoint+1], NO_FUNCTION, &PRom[R_Lim_Inf+1], &PRom[R_Lim_Sup+1], CHAN_2},
/*SP3*/{&PRom[R_SetPoint+2], NO_FUNCTION, &PRom[R_Lim_Inf+2], &PRom[R_Lim_Sup+2], CHAN_3},
/*SP4*/{&PRom[R_SetPoint+3], NO_FUNCTION, &PRom[R_Lim_Inf+3], &PRom[R_Lim_Sup+3], CHAN_4},

/*AL1 */{&PRom[R_AL+0], NO_FUNCTION, &Lim_Inf_ch[0], &Lim_Sup_ch[0], CHAN_1},								 //4
/*AL2 */{&PRom[R_AL+1], NO_FUNCTION, &Lim_Inf_ch[0], &Lim_Sup_ch[0], CHAN_1},
/*AL3 */{&PRom[R_AL+2], NO_FUNCTION, &Lim_Inf_ch[0], &Lim_Sup_ch[0], CHAN_1},
/*AL4 */{&PRom[R_AL+3], NO_FUNCTION, &Lim_Inf_ch[0], &Lim_Sup_ch[0], CHAN_2},

/*None1*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},
/*None2*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*None3*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*None4*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},

#ifndef _APARATO_VIEJO
/*H1*/{&PRom[R_H1+0], NO_FUNCTION, &Lim_0, &Lim_Sup_ch[0], CHAN_1},													 //12
/*H2*/{&PRom[R_H1+1], NO_FUNCTION, &Lim_0, &Lim_Sup_ch[0], CHAN_2},
/*H3*/{&PRom[R_H1+2], NO_FUNCTION, &Lim_0, &Lim_Sup_ch[0], CHAN_3},
/*H4*/{&PRom[R_H1+3], NO_FUNCTION, &Lim_0, &Lim_Sup_ch[0], CHAN_4},

/*HA1*/{&PRom[R_HA1+0], NO_FUNCTION, &Lim_0, &Lim_Sup_ch[0], CHAN_1},												 //16
/*HA2*/{&PRom[R_HA1+1], NO_FUNCTION, &Lim_0, &Lim_Sup_ch[0], CHAN_2},
/*HA3*/{&PRom[R_HA1+2], NO_FUNCTION, &Lim_0, &Lim_Sup_ch[0], CHAN_3},
/*HA4*/{&PRom[R_HA1+3], NO_FUNCTION, &Lim_0, &Lim_Sup_ch[0], CHAN_4},
#else
/*H1*/{&PRom[R_H1+0], NO_FUNCTION, &Lim_m1999, &Lim_9999, CHAN_1},									 
/*H2*/{&PRom[R_H1+1], NO_FUNCTION, &Lim_m1999, &Lim_9999, CHAN_2},
/*H3*/{&PRom[R_H1+2], NO_FUNCTION, &Lim_m1999, &Lim_9999, CHAN_3},
/*H4*/{&PRom[R_H1+3], NO_FUNCTION, &Lim_m1999, &Lim_9999, CHAN_4},

/*HA1*/{&PRom[R_HA1+0], NO_FUNCTION, &Lim_m1999, &Lim_9999, CHAN_1},								 
/*HA2*/{&PRom[R_HA1+1], NO_FUNCTION, &Lim_m1999, &Lim_9999, CHAN_2},
/*HA3*/{&PRom[R_HA1+2], NO_FUNCTION, &Lim_m1999, &Lim_9999, CHAN_3},
/*HA4*/{&PRom[R_HA1+3], NO_FUNCTION, &Lim_m1999, &Lim_9999, CHAN_4},
#endif
#ifdef _APARATO_VIEJO

/*PER1*/{&PRom[R_Per+0],NO_FUNCTION,&Lim_0,&Lim_10,CHAN_1},															 //20

/*PER2*/{&PRom[R_Per+1],NO_FUNCTION,&Lim_0,&Lim_10,CHAN_2},
/*PER3*/{&PRom[R_Per+2],NO_FUNCTION,&Lim_0,&Lim_10,CHAN_3},
/*PER4*/{&PRom[R_Per+3],NO_FUNCTION,&Lim_0,&Lim_10,CHAN_4},
#else
/*PER1*/{&PRom[R_Per+0],setPWM_period,&Lim_0,&Lim_10,CHAN_1},																 
/*PER2*/{&PRom[R_Per+1],setPWM_period,&Lim_0,&Lim_10,CHAN_2},
/*PER3*/{&PRom[R_Per+2],setPWM_period,&Lim_0,&Lim_10,CHAN_3},
/*PER4*/{&PRom[R_Per+3],setPWM_period,&Lim_0,&Lim_10,CHAN_4},
#endif
/*Sensor1*/{&PRom[R_Sensor+0],A_Sensor,&Lim_0,&Limite_sensor_Sup,CHAN_1},										 //24
/*Sensor2*/{&PRom[R_Sensor+1],A_Sensor,&Lim_0,&Limite_sensor_Sup,CHAN_2},
/*Sensor3*/{&PRom[R_Sensor+2],A_Sensor,&Lim_0,&Limite_sensor_Sup,CHAN_3},
/*Sensor4*/{&PRom[R_Sensor+3],A_Sensor,&Lim_0,&Limite_sensor_Sup,CHAN_4},


/*Decimales1*/{&PRom[R_Decimales+0],A_Decimales,&Lim_0, &Lim_Dec[0],CHAN_1},								 //28
/*Decimales2*/{&PRom[R_Decimales+1],A_Decimales,&Lim_0, &Lim_Dec[0],CHAN_2},
/*Decimales3*/{&PRom[R_Decimales+2],A_Decimales,&Lim_0, &Lim_Dec[0],CHAN_3},
/*Decimales4*/{&PRom[R_Decimales+3],A_Decimales,&Lim_0, &Lim_Dec[0],CHAN_4},


//andy
//*Offset1*/{&PRom[R_Offset+0],NO_FUNCTION,&Lim_Inf_ch[0], &Lim_Sup_ch[0],CHAN_1},
/*Offset1*/{&PRom[R_Offset+0],NO_FUNCTION,&Lim_m9999,&Lim_9999,CHAN_1},											 //32
/*Offset2*/{&PRom[R_Offset+1],NO_FUNCTION,&Lim_m9999, &Lim_9999,CHAN_2},
/*Offset3*/{&PRom[R_Offset+2],NO_FUNCTION,&Lim_m9999, &Lim_9999,CHAN_3},
/*Offset4*/{&PRom[R_Offset+3],NO_FUNCTION,&Lim_m9999, &Lim_9999,CHAN_4},
//andy

/*Gan1*/{&PRom[R_Gan+0],NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},														 //36
/*Gan2*/{&PRom[R_Gan+1],NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*Gan3*/{&PRom[R_Gan+2],NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*Gan4*/{&PRom[R_Gan+3],NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},

/*ACT1 */{&PRom[R_ACT+0],NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},													 //40
/*ACT2 */{&PRom[R_ACT+1],NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*ACT3 */{&PRom[R_ACT+2],NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*ACT4 */{&PRom[R_ACT+3],NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},

/*AGT1*/{&PRom[R_AGT+0],NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},														 //44
/*AGT2*/{&PRom[R_AGT+1],NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*AGT3*/{&PRom[R_AGT+2],NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*AGT4*/{&PRom[R_AGT+3],NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},

/*ACP1 */{&PRom[R_ACP+0],NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},													 //48
/*ACP2 */{&PRom[R_ACP+1],NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*ACP3 */{&PRom[R_ACP+2],NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*ACP4 */{&PRom[R_ACP+3],NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},

/*R_AGP*/{&PRom[R_AGP+0],NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},													 //52
/*R_AGP*/{&PRom[R_AGP+1],NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*R_AGP*/{&PRom[R_AGP+2],NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*R_AGP*/{&PRom[R_AGP+3],NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},

/*AAnlLow1*/{&PRom[R_AAnlLow+0],NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},										 //56
/*AAnlLow2*/{&PRom[R_AAnlLow+1],NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*AAnlLow3*/{&PRom[R_AAnlLow+2],NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*AAnlLow4*/{&PRom[R_AAnlLow+3],NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},

/*AAnlHi1*/{&PRom[R_AAnlHi+0],NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},											 //60
/*AAnlHi2*/{&PRom[R_AAnlHi+1],NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*AAnlHi3*/{&PRom[R_AAnlHi+2],NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*AAnlHi4*/{&PRom[R_AAnlHi+3],NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},


/*LimInferior1*/{&PRom[R_Lim_Inf+0],NO_FUNCTION,&Lim_Inf_ch[0],&PRom[R_Lim_Sup+0],CHAN_1},	 //64
/*LimInferior2*/{&PRom[R_Lim_Inf+1],NO_FUNCTION,&Lim_Inf_ch[0],&PRom[R_Lim_Sup+1],CHAN_2},
/*LimInferior3*/{&PRom[R_Lim_Inf+2],NO_FUNCTION,&Lim_Inf_ch[0],&PRom[R_Lim_Sup+2],CHAN_3},
/*LimInferior4*/{&PRom[R_Lim_Inf+3],NO_FUNCTION,&Lim_Inf_ch[0],&PRom[R_Lim_Sup+3],CHAN_4},

/*LimSuperior1*/{&PRom[R_Lim_Sup+0],NO_FUNCTION,&PRom[R_Lim_Inf+0],&Lim_Sup_ch[0],CHAN_1},	 //68
/*LimSuperior2*/{&PRom[R_Lim_Sup+1],NO_FUNCTION,&PRom[R_Lim_Inf+1],&Lim_Sup_ch[0],CHAN_2},
/*LimSuperior3*/{&PRom[R_Lim_Sup+2],NO_FUNCTION,&PRom[R_Lim_Inf+2],&Lim_Sup_ch[0],CHAN_3},
/*LimSuperior4*/{&PRom[R_Lim_Sup+3],NO_FUNCTION,&PRom[R_Lim_Inf+3],&Lim_Sup_ch[0],CHAN_4},

/*None1*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},
/*None2*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},																		 //72
/*None3*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*None4*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},

/*Tcontrol1*/{&PRom[R_Tcontrol1+0],NO_FUNCTION,&Lim_0,&Lim_2,CHAN_1},												 //76
/*Tcontrol2*/{&PRom[R_Tcontrol1+1],NO_FUNCTION,&Lim_0,&Lim_2,CHAN_2},
/*Tcontrol3*/{&PRom[R_Tcontrol1+2],NO_FUNCTION,&Lim_0,&Lim_2,CHAN_3},
/*Tcontrol4*/{&PRom[R_Tcontrol1+3],NO_FUNCTION,&Lim_0,&Lim_2,CHAN_4},

/*Reset1*/{&PRom[R_Reset+0],NO_FUNCTION,&Lim_Inf_ch[0],&Lim_Sup_ch[0],CHAN_1},							 //80
/*Reset2*/{&PRom[R_Reset+1],NO_FUNCTION,&Lim_Inf_ch[0],&Lim_Sup_ch[0],CHAN_2},
/*Reset3*/{&PRom[R_Reset+2],NO_FUNCTION,&Lim_Inf_ch[0],&Lim_Sup_ch[0],CHAN_3},
/*Reset4*/{&PRom[R_Reset+3],NO_FUNCTION,&Lim_Inf_ch[0],&Lim_Sup_ch[0],CHAN_4},

/*None1*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},
/*None2*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},																		 //84
/*None3*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*None4*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},

/*Integral1*/{&PRom[R_IN1+0],NO_FUNCTION,&Lim_0,&Lim_1000,CHAN_1},													 //88
/*Integral2*/{&PRom[R_IN1+1],NO_FUNCTION,&Lim_0,&Lim_1000,CHAN_2},
/*Integral3*/{&PRom[R_IN1+2],NO_FUNCTION,&Lim_0,&Lim_1000,CHAN_3},
/*Integral4*/{&PRom[R_IN1+3],NO_FUNCTION,&Lim_0,&Lim_1000,CHAN_4},

/*Derivada1 */{&PRom[R_DR1+0],NO_FUNCTION,&Lim_0,&Lim_600,CHAN_1},													 //92
/*Derivada2 */{&PRom[R_DR1+1],NO_FUNCTION,&Lim_0,&Lim_600,CHAN_2},
/*Derivada3 */{&PRom[R_DR1+2],NO_FUNCTION,&Lim_0,&Lim_600,CHAN_3},
/*Derivada4 */{&PRom[R_DR1+3],NO_FUNCTION,&Lim_0,&Lim_600,CHAN_4},

/*PeriodoA1*/{&PRom[R_Pra+0],NO_FUNCTION,&Lim_0,&Lim_10,AL_1},
/*PeriodoA2*/{&PRom[R_Pra+1],NO_FUNCTION,&Lim_0,&Lim_10,AL_2},														 //96
/*PeriodoA3*/{&PRom[R_Pra+2],NO_FUNCTION,&Lim_0,&Lim_10,AL_3},
/*PeriodoA4*/{&PRom[R_Pra+3],NO_FUNCTION,&Lim_0,&Lim_10,AL_4},

/*None1*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},																		 //100
/*None2*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*None3*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*None4*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},

/*LimPotInf1*/{&PRom[R_Pot_Inf+0],NO_FUNCTION,&Lim_0,&Lim_1000,CHAN_1},											//104
/*LimPotInf2*/{&PRom[R_Pot_Inf+1],NO_FUNCTION,&Lim_0,&Lim_1000,CHAN_2},
/*LimPotInf3*/{&PRom[R_Pot_Inf+2],NO_FUNCTION,&Lim_0,&Lim_1000,CHAN_3},
/*LimPotInf4*/{&PRom[R_Pot_Inf+3],NO_FUNCTION,&Lim_0,&Lim_1000,CHAN_4},

/*LimPotSup1 */{&PRom[R_Pot_Sup+0],NO_FUNCTION,&Lim_0,&Lim_1000,CHAN_1},										//108
/*LimPotSup2 */{&PRom[R_Pot_Sup+1],NO_FUNCTION,&Lim_0,&Lim_1000,CHAN_2},
/*LimPotSup3 */{&PRom[R_Pot_Sup+2],NO_FUNCTION,&Lim_0,&Lim_1000,CHAN_3},
/*LimPotSup4 */{&PRom[R_Pot_Sup+3],NO_FUNCTION,&Lim_0,&Lim_1000,CHAN_4},

/*Tsalcont1*/{&PRom[R_Tsalcont+0],NO_FUNCTION,&Lim_0,&Lim_3,CHAN_1},												//112
/*Tsalcont2*/{&PRom[R_Tsalcont+1],NO_FUNCTION,&Lim_0,&Lim_3,CHAN_2},
/*Tsalcont3*/{&PRom[R_Tsalcont+2],NO_FUNCTION,&Lim_0,&Lim_3,CHAN_3},
/*Tsalcont4*/{&PRom[R_Tsalcont+3],NO_FUNCTION,&Lim_0,&Lim_3,CHAN_4},

/*Potencia1 */{&PRom[R_Potman+0],NO_FUNCTION,&Lim_0,&Lim_1000,CHAN_1},											//116
/*Potencia2 */{&PRom[R_Potman+1],NO_FUNCTION,&Lim_0,&Lim_1000,CHAN_2},
/*Potencia3 */{&PRom[R_Potman+2],NO_FUNCTION,&Lim_0,&Lim_1000,CHAN_3},
/*Potencia4 */{&PRom[R_Potman+3],NO_FUNCTION,&Lim_0,&Lim_1000,CHAN_4},

//andy
//*AutoSintonia1*/{&PRom[R_Stn+0],A_Selftun,&Lim_0,&Lim_6,CHAN_1},
/*AutoSintonia1*/{&PRom[R_Stn+0],A_Selftun,&Lim_0,&Lim_2,CHAN_1},														//120
//andy


/*AutoSintonia2*/{&PRom[R_Stn+1],A_Selftun,&Lim_0,&Lim_2,CHAN_2},
/*AutoSintonia3*/{&PRom[R_Stn+2],A_Selftun,&Lim_0,&Lim_2,CHAN_3},
/*AutoSintonia4*/{&PRom[R_Stn+3],A_Selftun,&Lim_0,&Lim_2,CHAN_4},

#ifndef prog_viejo
/*RunPrograma1*/{&PRom[R_Programa+0],CorrerPrograma,&Lim_m1,&Lim_9,CHAN_1},									//124
/*RunPrograma2*/{&PRom[R_Programa+1],CorrerPrograma,&Lim_m1,&Lim_9,CHAN_2},
/*RunPrograma3*/{&PRom[R_Programa+2],CorrerPrograma,&Lim_m1,&Lim_9,CHAN_3},
/*RunPrograma4*/{&PRom[R_Programa+3],CorrerPrograma,&Lim_m1,&Lim_9,CHAN_4},
#else
/*RunPrograma1*/{&PRom[R_Programa+0],CorrerPrograma,&Lim_0,&Lim_10,CHAN_1},									
/*RunPrograma2*/{&PRom[R_Programa+1],CorrerPrograma,&Lim_0,&Lim_10,CHAN_2},
/*RunPrograma3*/{&PRom[R_Programa+2],CorrerPrograma,&Lim_0,&Lim_10,CHAN_3},
/*RunPrograma4*/{&PRom[R_Programa+3],CorrerPrograma,&Lim_0,&Lim_10,CHAN_4},
#endif


/*TipoA1*/{&PRom[R_T_AL+0],NO_FUNCTION,&Lim_0,&Lim_6,AL_1},																	//128
/*TipoA2*/{&PRom[R_T_AL+1],NO_FUNCTION,&Lim_0,&Lim_6,AL_2},
/*TipoA3*/{&PRom[R_T_AL+2],NO_FUNCTION,&Lim_0,&Lim_6,AL_3},
/*TipoA4*/{&PRom[R_T_AL+3],NO_FUNCTION,&Lim_0,&Lim_6,AL_4},

#ifdef programador									
/*Segmento1*/{&SegmentoMostrado[0],CambiarSegmento,&LimInf_Seg,&Lim_Segmento2[CHAN_1],CHAN_1},		//132
/*Segmento2*/{&SegmentoMostrado[1],CambiarSegmento,&LimInf_Seg,&Lim_Segmento2[CHAN_2],CHAN_2},
/*Segmento3*/{&SegmentoMostrado[2],CambiarSegmento,&LimInf_Seg,&Lim_Segmento2[CHAN_3],CHAN_3},
/*Segmento4*/{&SegmentoMostrado[3],CambiarSegmento,&LimInf_Seg,&Lim_Segmento2[CHAN_4],CHAN_4},
#else
/*Segmento1*/{NULL,CambiarSegmento,&LimInf_Seg,&Lim_Segmento2[CHAN_1],CHAN_1},
/*Segmento2*/{NULL,CambiarSegmento,&LimInf_Seg,&Lim_Segmento2[CHAN_2],CHAN_2},
/*Segmento3*/{NULL,CambiarSegmento,&LimInf_Seg,&Lim_Segmento2[CHAN_3],CHAN_3},
/*Segmento4*/{NULL,CambiarSegmento,&LimInf_Seg,&Lim_Segmento2[CHAN_4],CHAN_4},

#endif
//dan1001
#ifdef _APARATO_VIEJO
/*Talar1*/{&PRom[R_Talar1+0],CambiarAlarma,&Lim_0,&Lim_6,AL_1},
/*Talar2*/{&PRom[R_Talar1+1],CambiarAlarma,&Lim_0,&Lim_6,AL_2},															//136
/*Talar3*/{&PRom[R_Talar1+2],CambiarAlarma,&Lim_0,&Lim_6,AL_3},
/*Talar4*/{&PRom[R_Talar1+3],CambiarAlarma,&Lim_0,&Lim_6,AL_4},
#else
/*Talar1*/{&PRom[R_Talar1+0],CambiarAlarma,&Lim_0,&Lim_8,AL_1},
/*Talar2*/{&PRom[R_Talar1+1],CambiarAlarma,&Lim_0,&Lim_8,AL_2},
/*Talar3*/{&PRom[R_Talar1+2],CambiarAlarma,&Lim_0,&Lim_8,AL_3},
/*Talar4*/{&PRom[R_Talar1+3],CambiarAlarma,&Lim_0,&Lim_8,AL_4},
#endif
//dan1001

/*None1*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},																		//140
/*None2*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*None3*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*None4*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},

/*Filtro1*/{&PRom[R_Filtro1+0],NO_FUNCTION,&Lim_0,&Lim_255,CHAN_1},													//144
/*Filtro2*/{&PRom[R_Filtro1+1],NO_FUNCTION,&Lim_0,&Lim_255,CHAN_2},
/*Filtro3*/{&PRom[R_Filtro1+2],NO_FUNCTION,&Lim_0,&Lim_255,CHAN_3},
/*Filtro4*/{&PRom[R_Filtro1+3],NO_FUNCTION,&Lim_0,&Lim_255,CHAN_4},

/*TieSeg1*/{&TiempoEnMinutos[0],CambiarTiempo,&Lim_0,&Lim_TieSeg[CHAN_1],CHAN_1},						//148
/*TieSeg2*/{&TiempoEnMinutos[1],CambiarTiempo,&Lim_0,&Lim_TieSeg[CHAN_2],CHAN_2},
/*TieSeg3*/{&TiempoEnMinutos[2],CambiarTiempo,&Lim_0,&Lim_TieSeg[CHAN_3],CHAN_3},
/*TieSeg4*/{&TiempoEnMinutos[3],CambiarTiempo,&Lim_0,&Lim_TieSeg[CHAN_4],CHAN_4},

#ifdef CCAL
/*Pss1 */{&PRom[R_Pss],NO_FUNCTION,&Lim_0,&Lim_1000,CHAN_1},											          //152
/*Tss1 */{&PRom[R_Tss],NO_FUNCTION,&Lim_0,&Lim_1000,CHAN_1},											          //153
/*SPSS1*/{&PRom[R_SPlim], NO_FUNCTION,&PRom[R_Lim_Inf],&PRom[R_Lim_Sup],CHAN_1},	 
/*SPST1*/{&PRom[R_SPst], NO_FUNCTION,&PRom[R_Lim_Inf], &PRom[R_Lim_Sup], CHAN_1},	 

/*SPSB1*/{&PRom[R_SPsb], NO_FUNCTION,&PRom[R_Lim_Inf], &PRom[R_Lim_Sup], CHAN_1},	          //156 
/*Indf */{&PRom[R_Indf], NO_FUNCTION, &Lim_0,&Lim_9999,CHAN_1},	 
/*Indf */{&PRom[R_Drdf], NO_FUNCTION, &Lim_0,&Lim_1000,CHAN_1},	 
/*Indf */{&PRom[R_Abdf], NO_FUNCTION, &Lim_0,&Lim_9999,CHAN_1},	 

/*SPlimst*/{&PRom[R_SPlimst], NO_FUNCTION,&Lim_0,&Lim_1000,CHAN_1},        //160	 
/*None30*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*None31*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*None32*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},

/*None29*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},
/*None30*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*None31*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*None32*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},

/*None29*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},
/*None30*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*None31*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*None32*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},

/*None33*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},
/*None34*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*None35*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*None36*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},

/*None37*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},
/*None38*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*None39*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*None40*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},

/*None41*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},
/*None42*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*None43*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*None44*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},

/*None45*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},
/*None46*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*None47*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*None48*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},

/*None49*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},
/*None50*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*None51*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*None52*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},

#else
/*None13*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},																		//152
/*None14*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*None15*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*None16*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},

/*None17*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},
/*None18*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*None19*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*None20*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},

/*None21*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},
/*None22*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*None23*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*None24*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},

/*None25*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},
/*None26*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*None27*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*None28*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},

/*None29*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},
/*None30*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*None31*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*None32*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},

/*None33*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},
/*None34*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*None35*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*None36*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},

/*None37*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},
/*None38*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*None39*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*None40*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},

/*None41*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},
/*None42*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*None43*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*None44*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},

/*None45*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},
/*None46*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*None47*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*None48*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},

/*None49*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},
/*None50*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*None51*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*None52*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},

#endif



/*None53*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},
/*None54*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*None55*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*None56*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},
/*None57*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},
/*None58*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*None59*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*None60*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},
/*None61*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},
/*None62*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*None63*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*None64*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},
/*None65*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},
/*None66*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*None67*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*None68*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},
/*None69*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},
/*None70*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*None71*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*None72*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},
/*None73*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},
/*None74*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*None75*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},



/*vramp*/{&PRom[R_Vrmp],NO_FUNCTION,&Lim_0,&Lim_1000,0},
/*tmpmes*/{&PRom[R_Tmpm],NO_FUNCTION,&Lim_0,&Lim_1000,0},
/*tiemes*/{&PRom[R_Tiem],NO_FUNCTION,&Lim_0,&Lim_1000,0},

/*topn*/{&PRom[R_Topn],NO_FUNCTION,&Lim_0,&Lim_1000,0},
/*dbnd*/{&PRom[R_Dbnd],NO_FUNCTION,&Lim_0,&Lim_600,0},



/*SetC*/{&PRom[R_SetC],NO_FUNCTION,&Lim_0,&Lim_9999,0},
/*Version*/{&PRom[R_Ver],NO_FUNCTION,&Lim_0,&Lim_6,0},
/*Id*/{&PRom[R_Id],NO_FUNCTION,&Lim_0,&Lim_255,0},
#ifdef adquisidor
/*Adq*/{&PRom[R_adq],A_Adquiriendo,&Lim_0,&Lim_2,0},
/*Ano*/{&PRom[R_Ano],NO_FUNCTION,&Lim_2006,&Lim_2099,0},
/*Mes*/{&PRom[R_mes],NO_FUNCTION,&Lim_0,&Lim_12,0},
/*Dia*/{&PRom[R_dia],NO_FUNCTION,&Lim_0,&Lim_0,0},
/*Hora*/{&PRom[R_Hora],NO_FUNCTION,&Lim_0,&Lim_0,0},
/*Intervalo*/{&PRom[R_int],NO_FUNCTION,&Lim_1,&Lim_9999,0},
#else
/*None0*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*None1*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
/*None2*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_4},
/*None3*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_1},
/*None4*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_2},
/*None5*/{NULL,NO_FUNCTION,&Lim_m1999,&Lim_9999,CHAN_3},
#endif
/*ATA*/{&PRom[R_ATA],NO_FUNCTION,&Lim_m1999,&Lim_9999,0},			 						
};
								
/* pantalla principal */
/*****************************/


#ifdef SIMCIC

const Numerico Principal1={
      MainHandler,								/* funcion que procesa al box*/
      &Parametros[R_SetPoint],		/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"Pri ",											/* texto del titulo */
			1,													/* punto decimal a enc */
			NULL,
			(PunteroF*)&Vrmp.DirProc,&Codigo1.DirProc,					      //Proximos estados
			};

#elif	 defined(CCAL)
const PunteroF R_Principal1[3]={

			&Ccalstn.DirProc,
      &Ccalstn.DirProc,		                                      //Proximos estados
      &C1POT.DirProc,		                                        //Proximos estados

};

const Numerico Principal1={
      MainHandler,								                              /* funcion que procesa al box*/
      &Parametros[R_SetPoint],					                        /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"Pri ",											                              /* texto del titulo */
			1,													                              /* punto decimal a enc */
			&PRom[R_Tsalcont],								                        //Parametro que decide el proximo estado
			R_Principal1,
			&Codigo1.DirProc
};

#else
const PunteroF R_Principal1[6]={

      #ifdef CCAL
			&Ccalstn.DirProc,
      #else
      &C1SP.DirProc,		                                        //Proximos estados. Con bl1 voy al sp
			#endif


			&Sintonia.DirProc,	                                      //Con bl2 voy a tun
			NULL,                                                     //con bl3 a ninguna parte 
			&Tmpm.DirProc,			                                                //con bkr a sp con otro nombre
			#ifdef jony_18_07
			&Tmpm.DirProc,		                                        //con bkr1 igual que con bkr
			&C1SP.DirProc	                                            //Sacar, esta pq el numero de versionesta en version 
			#endif
};

const Numerico Principal1={
      MainHandler,								                              /* funcion que procesa al box*/
      &Parametros[R_SetPoint],					                        /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"Pri ",											                              /* texto del titulo */
			1,													                              /* punto decimal a enc */
			&PRom[R_Ver],								                              //Parametro que decide el proximo estado
			R_Principal1,
			&Codigo1.DirProc
};

#endif

/*setpoints y alarmas*/			
/*****************************/

#ifdef CCAL
const PunteroF R_C1SP[3]={
      &AL1.DirProc,						                        //Proximos estados
			&AL1.DirProc,						                        //Proximos estados
			&AL1.DirProc,						                      //Proximos estados
};

#else
const PunteroF R_C1SP[3]={
      &AL1.DirProc,						                        //Proximos estados
			&AL1.DirProc,						                        //Proximos estados
			&C1POT.DirProc,						                      //Proximos estados
};

#endif


const Numerico C1SP={
      #ifdef pirani
      NumExpoHandler,
      #else
      NumHandler,									                      /* funcion que procesa al box*/
      #endif
      &Parametros[0],					                      /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"SP 1",							                              /* texto del titulo */
			DECIMALES_CANAL1,						                      //pos punto dec
			(int*)&PRom[R_Tsalcont],									        //Parametro que modifica
			R_C1SP,NULL						                            //Proximos estados
			};

const Numerico C1POT={
      NumHandler,									                      /* funcion que procesa al box*/
      &Parametros[R_Potman],					                        /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"Pot1",							                              /* texto del titulo */
			1,											                          //pos punto dec
			NULL,									                            //Parametro que modifica
			(const PunteroF*) &AL1.DirProc,NULL						  //Proximos estados
			};
			

const Numerico AL1=	                                  //nombre variable
      {
      #ifdef pirani
      NumExpoHandler,
      #else
      NumHandler,									                      /* funcion que procesa al box*/
      #endif						                          // funcion que procesa al box
      &Parametros[R_AL],										                  // direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor
			"A  1",							                              //nombre display
			DECIMALES_CANAL1,								                  //pos punto dec
			NULL,							                                //parametro que modifica. 
      #if ALARMAS_CH1 > 1
			  (PunteroF*)&AL2.DirProc,NULL			          //enter rap,enter mant		
      #else
			  #ifdef programador
			  (PunteroF*)&P1.DirProc,NULL			 //enter rap,enter mant
			  #else
			    #if CANTIDAD_SAL_CONTROL>1
    			(PunteroF*)&C2SP.DirProc,NULL
					#else
  			  (PunteroF*)&Principal1.DirProc,NULL			          //enter rap,enter mant		
          #endif
			  #endif
      #endif
			};

const Numerico AL2 =	                                //nombre variable
      {
      #ifdef pirani
      NumExpoHandler,
      #else
      NumHandler,									                      /* funcion que procesa al box*/
      #endif						                          // funcion que procesa al box
      &Parametros[R_AL+1],											              // direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor
			"A  2",							                              //nombre display
			DECIMALES_CANAL1,											            //pos punto dec
			NULL,							                                //parametro que modifica. 
      #if ALARMAS_CH1 > 2
			(PunteroF*)&AL3.DirProc,NULL			          //enter rap,enter mant		
      #else
			#ifdef programador
			(PunteroF*)&P1.DirProc,NULL			 //enter rap,enter mant
			#else
			(PunteroF*)&Principal1.DirProc,NULL			          //enter rap,enter mant		
			#endif
      #endif
			};


const Numerico AL3 =	                                //nombre variable
      {
      #ifdef pirani
      NumExpoHandler,
      #else
      NumHandler,									                      /* funcion que procesa al box*/
      #endif						                          // funcion que procesa al box
      &Parametros[R_AL+2],											              // direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor
			"A  3",							                              //nombre display
			DECIMALES_CANAL1,											            //pos punto dec
			NULL,							                                //parametro que modifica. 
#ifdef EQA1
			(PunteroF*)&C1STN.DirProc,NULL				//enter rap,enter mant			
#else
			#ifdef programador
			(PunteroF*)&P1.DirProc,NULL			 //enter rap,enter mant
			#else
			(PunteroF*)&Principal1.DirProc,NULL			          //enter rap,enter mant		
			#endif
#endif
			};
								 
#ifdef programador

const Numerico P1 =	                                    //nombre variable
      {NumHandler,						                          // funcion que procesa al box
      &Parametros[R_Programa],											          // direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor
			"P  1",							                              //nombre display
			0,											                          //pos punto dec
			NULL,							                                //parametro que modifica. 
			#if CANTIDAD_SAL_CONTROL>1
			(PunteroF*)&C2SP.DirProc,NULL
			#else
			(PunteroF*)&Principal1.DirProc,NULL			 //enter rap,enter mant
			#endif
			};


/*#ifndef prog_viejo 

const NumericoRO Segmento1 =	                                    //nombre variable
      {NumHandler,						                          // funcion que procesa al box
      &SegmentoActual[0],											          // direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor
			"SEG1",							                              //nombre display
			0,											                          //pos punto dec	
			NULL,							                                //parametro que modifica. 
			(PunteroF*)&SegundosSegmento1.DirProc,NULL			 //enter rap,enter mant
			};

const NumericoRO SegundosSegmento1 =	                                    //nombre variable
      {Num_realtime_Handler,	                          // funcion que procesa al box
      ((int *)&SegundosSegmento[0])+1,										          // direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor
			"tIE1",							                              //nombre display
			0,											                          //pos punto dec
			NULL,							                                //parametro que modifica. 
			(PunteroF*)&AL1.DirProc,NULL			 //enter rap,enter mant
			};

#else		*/

const Numerico Segmento1 =	                                    //nombre variable
      {NumHandler,						                          // funcion que procesa al box
      &Parametros[R_Segmento],											          // direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor
			"SEG1",							                              //nombre display
			0,											                          //pos punto dec	
			NULL,							                                //parametro que modifica. 
			(PunteroF*)&SegundosSegmento1.DirProc,NULL			 //enter rap,enter mant
			};

const Numerico SegundosSegmento1 =	                                    //nombre variable
      {TieSegHandler,	                          // funcion que procesa al box
      &Parametros[R_TieSeg],										          // direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor
			"tIE1",							                              //nombre display
			0,											                          //pos punto dec
			NULL,							                                //parametro que modifica. 
			(PunteroF*)&AL1.DirProc,NULL			 //enter rap,enter mant
			};			
/*#endif*/




#endif
			
#if CANTIDAD_CANALES>1
/**********SET POINT 2**************/
/***********************************/
const PunteroF R_C2SP[3]={
      &C2AL1.DirProc,						                        //Proximos estados
			&C2AL1.DirProc,						                        //Proximos estados
			&C2POT.DirProc,						                        //Proximos estados
};
const Numerico C2SP={
      #ifdef pirani
      NumExpoHandler,
      #else
      NumHandler,									                      /* funcion que procesa al box*/
      #endif									                      /* funcion que procesa al box*/
      &Parametros[R_SetPoint+1],        				                      /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"SP 2",							                              /* texto del titulo */
			DECIMALES_CANAL2,											            //pos punto dec
			&PRom[R_Tsalcont+1],									      //Parametro que modifica
			R_C2SP,NULL						                                  //Proximos estados
			};

/**********Potencia 2**************/
/***********************************/
const Numerico C2POT={
      NumHandler,									                      /* funcion que procesa al box*/
      &Parametros[R_Potman+1],				                        /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"Pot2",							                              /* texto del titulo */
			1,											                          //pos punto dec
			NULL,									                            //Parametro que modifica
			(const PunteroF*)&C2AL1.DirProc,NULL						  //Proximos estados
			};

/**********Alarma ch2 al1***********/
/***********************************/
const Numerico C2AL1 =	                                //nombre variable
      {NumHandler,						                          // funcion que procesa al box
      &Parametros[R_AL+1],											              // direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor
			"A  2",							                              //nombre display
			DECIMALES_CANAL2,											            //pos punto dec
			NULL,							                                //parametro que modifica. 
//			(PunteroF*)&C2SP.DirProc,NULL			          //enter rap,enter mant		

			#ifdef programador
			(PunteroF*)&P2.DirProc,NULL			 //enter rap,enter mant
			#else
			(PunteroF*)&Principal1.DirProc,NULL			          //enter rap,enter mant		
			#endif
			};

const Numerico P2 =	 //nombre variable
      {NumHandler,						 /* funcion que procesa al box*/
      &Parametros[R_Programa+1],											 /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"P  2",							 //nombre display
			0,											 //pos punto dec
			NULL,							 //parametro que modifica. 
			(const PunteroF*)&Principal1.DirProc,NULL			 //enter rap,enter mant
			};
			
#endif

/* Codigo */
/**********/
const TDato dCodigo={
  	 NULL,		/* Direccion donde se encuentra el dato*/			 
  	 NO_FUNCTION,					/* Funcion a llamar luego de la escritura del dato*/
  	 &Lim_0, &Lim_9999,	 /*Limites inferior y superior del dato*/
		 CHAN_1
};

const Numerico Codigo1={
      CodHandler,				/* funcion que procesa al box*/
      &dCodigo,						/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"cod ",				    //nombre display
			0,								/* punto decimal a enc */
			NULL,						  //parametro que modifica.
//			#ifdef adquisidor 
//			NULL,&Adquisicion.DirProc			//Proximos estados en bl1, primero toque r�pido luego toque prolongado
//			#else
			#ifdef programador
			NULL,&Programas.DirProc			//Proximos estados en bl1, primero toque r�pido luego toque prolongado
			#else
			NULL,&Sintonia.DirProc			//Proximos estados en bl1, primero toque r�pido luego toque prolongado
			#endif
//			#endif
			};
			
						
/* Definicion de los titulos */
/*****************************/
#ifdef adquisidor
 
const Titulo Adquisicion={ 
      TitleHandler,										// funcion que procesa al box
			"MEM ",													//nombre display
			" -- ",													//nombre display
			NULL,											  //parametro que modifica.
			#ifdef programador
			(PunteroF*)&Adqui_State.DirProc,&Programas.DirProc	//Proximos estados	
			#else
			(PunteroF*)&Adqui_State.DirProc,&Sintonia.DirProc		//Proximos estados	
			#endif
			};

#endif

#ifdef programador

const Titulo Programas={ 
      #ifdef prog_viejo
      TitleProgHandler,
      #else
      TitleHandler,										/* funcion que procesa al box*/
			#endif
			"ProG",													//nombre display
			" -- ",													//nombre display
			NULL,											  //parametro que modifica.
		 #ifdef prog_viejo
		 (PunteroF*)&Temp_i.DirProc,
		 #else
		 (PunteroF*)&Program.DirProc,
		 #endif
		 &Sintonia.DirProc		//Proximos estados
			};
#endif


const Titulo Sintonia={ 
      TitleHandler,							/* funcion que procesa al box*/
			"tun ",										//nombre display
			"SintoniA   ",										//nombre display
			NULL,								//parametro que modifica.

		#ifdef CCAL
			(PunteroF*)&C1RES.DirProc,&Colcal.DirProc,					//Proximos estados
    #else
			(PunteroF*)&C1RES.DirProc,&Calibracion.DirProc,					//Proximos estados
		#endif
			};

const Titulo Calibracion={ 
      TitleHandler,						/* funcion que procesa al box*/
			"cAL ",									//nombre display
			"cALibrAcion   ",									//nombre display
			NULL,							//parametro que modifica.
			(PunteroF*)&TipoSensor1.DirProc,&Setting.DirProc  //Proximos estados
			};



//dan1001
#ifdef _APARATO_VIEJO
/*Set aparato viejo*/
/*******************/
const Titulo Setting={ 
      TitleHandler,									/* funcion que procesa al box*/
			"SEt ",												//nombre display
			"conFiGurAcion   ",												//nombre display
			NULL,												//parametro que modifica.
			(PunteroF*)&C1TSC.DirProc,&Limites.DirProc				//Proximos estados
			};
#else
/*Set aparato nuevo*/
/*******************/
const Titulo Setting={ 
      TitleHandler,									/* funcion que procesa al box*/
			"SEt ",												//nombre display
			" -- ",												//nombre display
			NULL,												//parametro que modifica.
			(PunteroF*)&C1CN.DirProc,&Limites.DirProc				//Proximos estados
			};

#endif
//dan1001

const Titulo Limites={ 
      TitleHandler,										/* funcion que procesa al box*/
			"LiM ",													//nombre display
			"LiMitES   ",													//nombre display
			NULL,											//parametro que modifica.
			(PunteroF*)&LimiteInferior1.DirProc,&Principal1.DirProc		//Proximos estados
			};
			

/* PARAMETROS de "Limites" */
/***************************/

/* limite inferior del set-point de control principal*/ 
const Numerico LimiteInferior1={
      NumHandler,
      &Parametros[R_Lim_Inf],
			"Li 1",
			DECIMALES_CANAL1,
			NULL,
			(PunteroF*)&LimiteSuperior1.DirProc,NULL
			};
			


/* limite superior del set-point de control principal*/  
const Numerico LimiteSuperior1={
      NumHandler,
      &Parametros[R_Lim_Sup],
			"LS 1",
			DECIMALES_CANAL1,
			NULL,
			(PunteroF*)&PotenciaInferior1.DirProc,NULL
			};
						

/* limite inferior de potencia de control principal*/ 
const Numerico PotenciaInferior1={
      NumHandler,
      &Parametros[R_Pot_Inf],
			"Pi 1",
			1,
			NULL,
			(PunteroF*)&PotenciaSuperior1.DirProc,NULL
			};
			
			
/* limite superior de potencia de control principal*/  
const Numerico PotenciaSuperior1={
      NumHandler,
      &Parametros[R_Pot_Sup],
			"PS 1",
			1,
			NULL,	 
			#if CANTIDAD_SAL_CONTROL >1
					#ifdef SP_EXTERNO
    			  (PunteroF*)&Principal1.DirProc,NULL
					#else
    			  (PunteroF*)&LimiteInferior2.DirProc,NULL
					#endif
			#else
			(PunteroF*)&Principal1.DirProc,NULL
			#endif

			};
			
#if CANTIDAD_CANALES >1
const Numerico LimiteInferior2={
      NumHandler,
      &Parametros[R_Lim_Inf+1],
			"Li 2",
			DECIMALES_CANAL2,
			NULL,
			(PunteroF*)&LimiteSuperior2.DirProc,NULL
			};

const Numerico LimiteSuperior2={
      NumHandler,
      &Parametros[R_Lim_Sup+1],
			"LS 2",
			DECIMALES_CANAL2,
			NULL,
			(PunteroF*)&PotenciaInferior2.DirProc,NULL
			};

const Numerico PotenciaInferior2={
      NumHandler,
      &Parametros[R_Pot_Inf+1],
			"Pi 2",
			1,
			NULL,
			(PunteroF*)&PotenciaSuperior2.DirProc,NULL
			};

const Numerico PotenciaSuperior2={
      NumHandler,
      &Parametros[R_Pot_Sup+1],
			"PS 2",
			1,
			NULL,
	    (PunteroF*)&Principal1.DirProc,NULL
      };

#endif




#endif


/* fin  */


