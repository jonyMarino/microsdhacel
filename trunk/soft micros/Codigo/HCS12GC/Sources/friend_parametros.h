#ifndef _FRIEND_PARAMETROS
#define _FRIEND_PARAMETROS

#include "Mydefines.h"
#include "parametros.h"

  /*Histeresis*/
  extern const TDato ParH;
  
  /*Histeresis Alarma*/
  extern const TDato ParHA;
  
  /*Sensor*/
  extern const TDato ParSensor;
  
  
  /*Decimales*/
  extern const TDato ParDecimales;
  
  /*Tcontrol*/
  #ifndef _APARATO_VIEJO
  extern const TDato ParTipoControl;
  #endif
  
  /*PeriodoA*/
  extern const TDato ParPeriodoAlarma;
  /*AutoSintonia*/
  extern const TDato ParSelfTun;
  
  #ifdef _PROGRAMADOR
  
  /*Programa*/
  extern const TDato ParPrograma;
  
  /*Segmento*/
  extern const TDato ParSegmento;

  /*TieSeg*/
  extern const TDato ParTiempoSegActual;
  
  #endif
  
  #ifdef adquisidor
  /*Adq*/{&PRom[R_adq],A_Adquiriendo,get_lim0,get_lim1,0},
  /*Ano*/{&PRom[R_Ano],2007,2500,0},
  /*Mes*/{&PRom[R_mes],0,12,0},
  /*Dia*/{&PRom[R_dia],0,0,0},
  /*Hora*/{&PRom[R_Hora],0,0,0},
  /*Intervalo*/{&PRom[R_int],1,MAX_NUMBER_DISP,0},
  #endif
/*extern const TDato Parametros1[]={

  			 						
};  */

  /*SP*/
  extern const TDato ParSP;
  /*AL */
  extern const TDato ParAL; 
  
  /*Limite Inferior del SetPoint*/
  extern const TDato ParLimInfSP;

  /*Limite Superior del SetPoint*/
  extern const TDato ParLimSupSP;
  /*Reset1*/
  extern const TDato ParReset;
  /*Filtro*/
  extern const TDato ParFiltro;

  /*Periodo*/
  extern const TDato ParPeriodo;
  /*Offset*/
  extern const TDato ParOffset;

  /*Gan1*/
  extern const TDato ParGanancia;

  /*Ajuste Cero Termopar */
  extern const TDato ParAjCeroT;

  /*Ajuste Gan Termopar */
  extern const TDato ParAjGanT;

  /*Ajuste Cero PT100 */
  extern const TDato ParAjCeroPT;

  /*Ajuste Gan PT100*/
  extern const TDato ParAjGanPT;
  /*Ajuste Retransmision Analogico Valor Low*/
  extern const TDato ParRetLow;

  /*Ajuste Retransmision Analogico Valor Hi*/
  extern const TDato ParRetHi;

  /*Integral*/
  extern const TDato ParIntegral;

  /*Derivada*/
  extern const TDato ParDerivada;

  /*TipoAL*/
  extern const TDato ParTipoAlarma1;


  /*Talar*/
  extern const TDato ParTipoAlarma2;
  /*LimPotInf1*/
  extern const TDato ParLimPotInf;

  /*LimPotSup*/
  extern const TDato ParLimPotSup;

  /*Tsalcont*/
  extern const TDato ParTipoSalControl;
  /*Potencia*/
  extern const TDato ParPotencia;

  /*SetC*/
  extern const TDato ParSetC;
  /*Variable del Main*/
  extern const TDato ParVarMain;
  /*Version*/
  extern const TDato ParVersion;
  /*Id*/
  extern const TDato ParId;
  /*Ajuste Temperatura Ambiente*/
  extern const TDato ParAjTempAmb;
  
  /*  Tiempo de Valvula Proporcional  */
  extern const TDato ParVpTime;  
  /*  Banda Muerta de Valvula Proporcional  */
  extern const TDato ParVpDeadB;
  
  /**********************/
  /*    PROGRAMADOR     */ 
  /**********************/

  extern const TDato ParProgConf;
  extern const TDato ParSegConf;
  #if !defined( prog_viejo)
    extern const TDato ParTtiConf;
    extern const TDato ParTiConf;
    extern const TDato ParTTolGral;
    extern const TDato ParTolGral;
    extern const TDato ParCondEGral;
    extern const TDato ParOnEnd;
    extern const TDato ParTSeg;
    extern const TDato ParJumpPrg;
    extern const TDato ParTTol;
  #endif
  extern const TDato ParSegSP;
  extern const TDato ParTiempoSeg;
  extern const TDato ParTol;
  extern const TDato ParCondE;
    /*programador viejo*/
    extern const TDato ParTemp_ini;
    
 /*    COLADA CALIENTE   */
/************************/
#ifdef _COLADA_CALIENTE
  /*Potencia*/
  extern const TDato ParCC_Pot;
	/*Constante*/
	extern const TDato ParCC_Const;
	/*Tiempo*/
	extern const TDato ParCC_TiempoSS;
	/*  Ciclo en Segundos de Potencia Critica y Potencia de Relajo*/
  extern const TDato ParCC_PotCicle;
  /* Tiempo en Segundos en que se puede estar en potencia critica*/
  extern const TDato ParCC_CritPotTime;
  /*  Limite Inferior de Potencia Critica */
  extern const TDato ParCC_CritPot;
  /*  Limite Superior de la Potencia de Relajo */
  extern const TDato ParCC_RelaxPot;
 #endif
  
#endif
