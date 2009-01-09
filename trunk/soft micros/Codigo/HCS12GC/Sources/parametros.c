#include "Mydefines.h"
#include "IFsh10.h"
#include "cnfbox.h"
#include "boxes.h"
#include "parametros.h"
#include "friend_parametros.h"
#include "Programador.h"
#include "Sensores.h"
#include "Alarmas.h"
#include "SelfTune.h"
#ifdef _COLADA_CALIENTE
  #include "ControlCC.h"
#else
  #include "Control.h"
#endif
#include "boxesset.h"
#include "modbus.h"
#include "ramp_to_sp.h"
#include "ValvulaP.h"

#pragma CONST_SEG DEFAULT 
#pragma STRING_SEG DEFAULT
																					 
  
int get_Lim_min_display(byte a){return MIN_NUMBER_DISP;}

int get_Lim_max_display(byte a){return MAX_NUMBER_DISP;}
void EmptyFunction(void){}

#ifdef _APARATO_VIEJO
  #define get_LimInf_H  get_Lim_min_display
#else
  #define get_LimInf_H  get_Lim_0 
#endif 
  

  
  /*Histeresis Alarma*/
  const TDato ParHA={
    get_H_Alarma, set_H_Alarma, get_LimInf_H, get_Lim_max_display
  }; // funcion: AL_SetearOnOff  ; Limites: 0, 9999

  

  
  /*PeriodoA*/
  const TDato ParPeriodoAlarma={
    get_PeriodoAlarma,set_PeriodoAlarma,get_Lim_0,get_LimSup_PeriodoAlarma
  };		// funcion: setPWM_period  ; Limites: 0, 9
    
  /*AutoSintonia*/
  const TDato ParSelfTun={
    get_SelfTun,set_SelfTun,get_Lim_0,get_LimSup_SelfTun
  }; // funcion: A_Selftun  ; Limites: 0, NUM_SELFTUNES-1
  
  #ifdef _PROGRAMADOR
  /*Programa*/
  const TDato ParPrograma={
    get_Programa,set_Programa,get_Lim_0,get_LimSup_Programa
  }; // funcion: CorrerPrograma  ; Limites: 0, 9

  /*Segmento*/
  int get_Segmento(byte a){
    return get_iActualSegment(0)+1; //Control1  
  }
  
  byte set_Segmento(int val,byte a){
    return  set_ActualSegment(val-1,0); //Control1
  }
  
  int get_LimInf_Segmento(byte a){
    return 1;
  }
  int get_LimSup_Segmento(byte a){
    return MAX_SEGMENTOS;
  }
  const TDato ParSegmento={
    get_Segmento,set_Segmento,get_LimInf_Segmento,get_LimSup_Segmento
  }; // funcion: CambiarSegmento  ; Limites: 1, &Lim_Segmento2[OUT_CNTR_1]


  /*TieSeg*/
  const TDato ParTiempoSegActual={
    get_TiempoMinutos,set_TiempoMinutos,get_Lim_0,get_Lim_max_display
  };				// funcion: CambiarTiempo  ; Limites: 0, Lim_TieSeg[0]
  
  #endif
  
  #ifdef adquisidor
  /*Adq*/{&PRom[R_adq],A_Adquiriendo,get_lim0,get_lim1,0},
  /*Ano*/{&PRom[R_Ano],2007,2500,0},
  /*Mes*/{&PRom[R_mes],0,12,0},
  /*Dia*/{&PRom[R_dia],0,0,0},
  /*Hora*/{&PRom[R_Hora],0,0,0},
  /*Intervalo*/{&PRom[R_int],1,MAX_NUMBER_DISP,0},
  #endif
/*const TDato Parametros1[]={

  			 						
};  */

  
  /*AL */
  const TDato ParAL={
    get_AL,set_AL, get_LimInf_AL, get_LimSup_AL
  };	 //&Lim_Inf_ch[0], &Lim_Sup_ch[0]


  /*Ajuste Retransmision Analogico Valor Low*/
  const TDato ParRetLow={
    get_RetLow,set_RetLow,get_Lim_min_display,get_LimSup_RetLow
  };

  /*Ajuste Retransmision Analogico Valor Hi*/
  const TDato ParRetHi={
    get_RetHi,set_RetHi,get_LimInf_RetHi,get_Lim_max_display
  };

  /*TipoAL*/
  const TDato ParTipoAlarma1={
    get_TipoAlarma1,set_TipoAlarma1,get_Lim_0,get_LimSup_TipoAlarma1
  };


  /*Talar*/
  const TDato ParTipoAlarma2={
    get_TipoAlarma2,set_TipoAlarma2,get_Lim_0,get_LimSup_TipoAlarma2
  };


  /*Variable del Main*/
  const TDato ParVarMain={
    get_DirPar,set_DirPar,get_LimInf_DirPar,get_LimSup_DirPar  
  };
  /*Version*/
  const TDato ParVersion={
    get_Version,set_Version,get_Lim_0,get_LimSup_Version
  };
  /*Id*/
  const TDato ParId={
    get_Id,set_Id,get_Lim_0,get_LimInf_Id
  };
  
  /*  Tiempo de Valvula Proporcional  */
  const TDato ParVpTime={
    get_VpTime,set_VpTime,get_LimInf_VpTime,get_Lim_max_display
  };
  
  /*  Banda Muerta de Valvula Proporcional  */
  const TDato ParVpDeadB={
    get_VpDeadB,set_VpDeadB,get_LimInf_VpDeadB,get_Lim_max_display  
  };

/**********************/
/*    PROGRAMADOR     */ 
/**********************/
  #ifdef _PROGRAMADOR
    byte programa_ingresado,segmento_ingresado;
    
   
    /*  Programa Ingresado  */  
      
    int get_ProgConf(byte a){
      return programa_ingresado+1;  
    }

    byte set_ProgConf(int val,byte a){
      programa_ingresado=val-1;
      return ERR_OK;  
    }
    
    int get_LimInf_ProgConf(byte a){
      return 1;  
    }  
    
    int get_LimSup_ProgConf(byte a){
      return MAX_PROGRAMAS+1;  
    }
       
    const TDato ParProgConf={
      get_ProgConf,set_ProgConf,get_LimInf_ProgConf,get_LimSup_ProgConf  
    };
    
    /*  Segmento Ingresado  */
    int get_SegConf(byte a){
      return segmento_ingresado+1;  
    }

    byte set_SegConf(int val,byte a){
      segmento_ingresado=val-1;
      return ERR_OK;  
    }
    
    int get_LimInf_SegConf(byte a){
      return 1;  
    }  
    
    int get_LimSup_SegConf(byte a){
      return get_Lim_Seg(programa_ingresado)+1;  
    }
       
    const TDato ParSegConf={
      get_SegConf,set_SegConf,get_LimInf_SegConf,get_LimSup_SegConf  
    }; 
		
		
		#if !defined( prog_viejo)
    
      /*  Tipo de temperatura inicial */
      int get_Tti(byte a){
        return Prg_get_TipoTempIni(programa_ingresado);  
      }

      byte set_Tti(int val,byte a){
        return Prg_set_TipoTempIni(val,programa_ingresado);
      }
      
      int get_LimInf_Tti(byte a){
        return 0;  
      }  
      
      int get_LimSup_Tti(byte a){
        return MAX_VALUE_TIPO_TEMP_INI;  
      }
         
      const TDato ParTtiConf={
        get_Tti,set_Tti,get_LimInf_Tti,get_LimSup_Tti  
      }; 
      
      /*  Temperatura inicial */
      
      int get_Ti(byte a){
        return Prg_get_TempIni(programa_ingresado);  
      }

      byte set_Ti(int val,byte a){
        return Prg_set_TempIni(val,programa_ingresado);
      }
      
      int get_LimInf_Ti(byte a){
        #if CANTIDAD_CANALES==1
          return get_LimInf_SP(a);
        #else
          return get_Lim_min_display(a);
        #endif    
      }  
      
      int get_LimSup_Ti(byte a){
        #if CANTIDAD_CANALES==1
          return get_LimSup_SP(a);
        #else
          return get_Lim_max_display(a);
        #endif    
      }
         
      const TDato ParTiConf={
        get_Ti,set_Ti,get_LimInf_Ti,get_LimSup_Ti  
      }; 
      
      /*  Tipo de tolerancia general  */
      int get_TTolGral(byte a){
        return Prg_getTipoTolGral(programa_ingresado);  
      }

      byte set_TTolGral(int val,byte a){
        return Prg_setTipoTolGral(val,programa_ingresado);
      }
      
      int get_LimInf_TTolGral(byte a){
        return 0;  
      }  
      
      int get_LimSup_TTolGral(byte a){
        return MAX_VALUE_TIPO_TOL_GRAL;  
      }
         
      const TDato ParTTolGral={
        get_TTolGral,set_TTolGral,get_LimInf_TTolGral,get_LimSup_TTolGral  
      }; 

      /*  Tolerancia general  */
      int get_TolGral(byte a){
        return Prg_getToleranciaGral(programa_ingresado);  
      }

      byte set_TolGral(int val,byte a){
        return Prg_setToleranciaGral(val,programa_ingresado);
      }
      
      int get_LimInf_TolGral(byte a){
        return get_Lim_min_display(a);  
      }  
      
      int get_LimSup_TolGral(byte a){
        return get_Lim_max_display(a);  
      }
         
      const TDato ParTolGral={
        get_TolGral,set_TolGral,get_LimInf_TolGral,get_LimSup_TolGral  
      }; 
      
      /*  Condicion de Emergencia general  */
      int get_CondEGral(byte a){
        return Prg_get_CondEmerGral(programa_ingresado);  
      }

      byte set_CondEGral(int val,byte a){
        return Prg_set_CondEmerGral(val,programa_ingresado);
      }
      
      int get_LimInf_CondEGral(byte a){
        return 0;  
      }  
      
      int get_LimSup_CondEGral(byte a){
        return MAX_VALUE_COND_GRAL;  
      }
         
      const TDato ParCondEGral={
        get_CondEGral,set_CondEGral,get_LimInf_CondEGral,get_LimSup_CondEGral  
      }; 
      
      /*  Condicion OnEnd  */
      int get_OnEnd(byte a){
        return Prg_get_OnEnd(programa_ingresado);  
      }

      byte set_OnEnd(int val,byte a){
        return Prg_set_OnEnd(val,programa_ingresado);
      }
      
      int get_LimInf_OnEnd(byte a){
        return 0;  
      }  
      
      int get_LimSup_OnEnd(byte a){
        return MAX_VALUE_ON_END;  
      }
         
      const TDato ParOnEnd={
        get_OnEnd,set_OnEnd,get_LimInf_OnEnd,get_LimSup_OnEnd  
      }; 

      /*  Tipo de Segmento*/
      int get_TSeg(byte a){
        return Prg_get_TipoSeg(programa_ingresado,segmento_ingresado);  
      }

      byte set_TSeg(int val,byte a){
        return Prg_set_TipoSeg(val,programa_ingresado,segmento_ingresado);
      }
      
      int get_LimInf_TSeg(byte a){
        return 0;  
      }  
      
      int get_LimSup_TSeg(byte a){
        return MAX_VALUE_TIPO_SEGMENTO;  
      }
         
      const TDato ParTSeg={
        get_TSeg,set_TSeg,get_LimInf_TSeg,get_LimSup_TSeg  
      }; 
    
    #endif !prog_viejo
    
    /*  Set Point de Segmento*/
    int get_SegSP(byte a){
      return Prg_get_SetPoint(programa_ingresado,segmento_ingresado);  
    }

    byte set_SegSP(int val,byte a){
      return Prg_set_SetPoint(val,programa_ingresado,segmento_ingresado);
    }
    
    int get_LimInf_SegSP(byte a){
      #if CANTIDAD_CANALES==1
        return get_LimInf_SP(a);
      #else
        return get_Lim_min_display(a);
      #endif      
    }  
    
    int get_LimSup_SegSP(byte a){
      #if CANTIDAD_CANALES==1
        return get_LimSup_SP(a);
      #else
        return get_Lim_max_display(a);
      #endif    
    }
    
    const TDato ParSegSP={
      get_SegSP,set_SegSP,get_LimInf_SegSP,get_LimSup_SegSP  
    };
    

    
    
    /* Tiempo de Segmento (Mismo para velocidad)*/
    int get_TiempoSeg(byte a){
      return Prg_get_Time(programa_ingresado,segmento_ingresado);  
    }

    byte set_TiempoSeg(int val,byte a){
      return Prg_set_Time(val,programa_ingresado,segmento_ingresado);
    }
    
    int get_LimInf_TiempoSeg(byte a){
        return 1; 
    }  
    
    int get_LimSup_TiempoSeg(byte a){
        return get_Lim_max_display(a);
    }
       
    const TDato ParTiempoSeg={
      get_TiempoSeg,set_TiempoSeg,get_LimInf_TiempoSeg,get_LimSup_TiempoSeg  
    }; 

		#if !defined(prog_viejo)
      /* Salto de programa en Segmento*/
      int get_JumpPrg(byte a){
        return Prg_get_JumpProg(programa_ingresado,segmento_ingresado)+1;  
      }

      byte set_JumpPrg(int val,byte a){
        return Prg_set_JumpProg(val-1,programa_ingresado,segmento_ingresado);
      }
      
      int get_LimInf_JumpPrg(byte a){
          return 1; 
      }  
      
      int get_LimSup_JumpPrg(byte a){
          return MAX_PROGRAMAS+1;
      }
         
      const TDato ParJumpPrg={
        get_JumpPrg,set_JumpPrg,get_LimInf_JumpPrg,get_LimSup_JumpPrg  
      };
      
      /*  Tipo de tolerancia  */
      int get_TTol(byte a){
        return Prg_getTipoTol(programa_ingresado,segmento_ingresado);  
      }

      byte set_TTol(int val,byte a){
        return Prg_setTipoTol(val,programa_ingresado,segmento_ingresado);
      }
      
      int get_LimInf_TTol(byte a){
        return 0;  
      }  
      
      int get_LimSup_TTol(byte a){
        return MAX_VALUE_TIPO_TOL;  
      }
         
      const TDato ParTTol={
        get_TTol,set_TTol,get_LimInf_TTol,get_LimSup_TTol  
      }; 
		#endif !prog_viejo
      /*  Tolerancia   */
      int get_Tol(byte a){
        return Prg_getTolerancia(programa_ingresado,segmento_ingresado);  
      }

      byte set_Tol(int val,byte a){
        return Prg_setTolerancia(val,programa_ingresado,segmento_ingresado);
      }
      
      int get_LimInf_Tol(byte a){
        return get_Lim_min_display(a);  
      }  
      
      int get_LimSup_Tol(byte a){
        return get_Lim_max_display(a);  
      }
         
      const TDato ParTol={
        get_Tol,set_Tol,get_LimInf_Tol,get_LimSup_Tol  
      }; 
    #ifndef prog_viejo  
      /*  Condicion de Emergencia  */
      int get_CondE(byte a){
        return Prg_get_CondEmer(programa_ingresado,segmento_ingresado);  
      }

      byte set_CondE(int val,byte a){
        return Prg_set_CondEmer(val,programa_ingresado,segmento_ingresado);
      }
      
      int get_LimInf_CondE(byte a){
        return 0;  
      }  
      
      int get_LimSup_CondE(byte a){
        return MAX_VALUE_COND_GRAL;  
      }
         
      const TDato ParCondE={
        get_CondE,set_CondE,get_LimInf_CondE,get_LimSup_CondE  
      }; 
  
    #endif !prog_viejo
    
      
      /* PROGRAMADOR VIEJO */
      /*********************/
      #ifdef prog_viejo
      /*  Enable Conf Programador */
      void En_ProgConf(void){
        programa_ingresado=0;
        segmento_ingresado=0;
      }
      
      /*Temperatura inicial*/
      int get_Temp_ini(byte a){
        return Prg_get_TempIni(programa_ingresado);
      }
      
      byte set_Temp_ini(int val,byte a){
         byte err;
          Prg_set_TipoTempIni(TEMP_INI_SET,programa_ingresado);
          Prg_setTipoTolGral(TTOL_NO,programa_ingresado);
          Prg_set_CondEmerGral(COND_NO,programa_ingresado); 
          Prg_set_OnEnd(END_KEEPCONECTED,programa_ingresado); 
         err|=Prg_set_TempIni(val,programa_ingresado);
         err|=Prg_set_TipoSeg(SEG_RMP_T,programa_ingresado,segmento_ingresado);   
         err|=Prg_setTipoTol(TTOL_HI,programa_ingresado,segmento_ingresado); 
        return err;
      }
      
      int get_LimInf_Temp_ini(byte a){
        #if CANTIDAD_CANALES==1
          return get_LimInf_SP(a);
        #else
          return get_Lim_min_display(a);
        #endif    
      }  
    
      int get_LimSup_Temp_ini(byte a){
        #if CANTIDAD_CANALES==1
          return get_LimSup_SP(a);
        #else
          return get_Lim_max_display(a);
        #endif    
      }
         
      const TDato ParTemp_ini={
        get_Temp_ini,set_Temp_ini,get_LimInf_Temp_ini,get_LimSup_Temp_ini  
      }; 
      
      
      /*  Condicion de Emergencia  */
        int get_CondE(byte a){
          if (Prg_get_TipoSeg(programa_ingresado,segmento_ingresado)==SEG_END)
            return MAX_VALUE_COND+1; //End 
          return Prg_getCondicionEmer(programa_ingresado,segmento_ingresado);  
        }

        byte set_CondE(int val,byte a){
          if (val == MAX_VALUE_COND+1)
            return Prg_set_TipoSeg(SEG_END,programa_ingresado,segmento_ingresado); //End 
          else{
     //       if(segmento_ingresado+1<MAX_SEGMENTOS){              
     //         Prg_set_TipoSeg(SEG_RMP_T,programa_ingresado,segmento_ingresado+1);   
     //         Prg_setTipoTol(TTOL_HI,programa_ingresado,segmento_ingresado+1);  
      //      }
            Prg_set_TipoSeg(SEG_RMP_T,programa_ingresado,segmento_ingresado);
            Prg_setTipoTol(TTOL_HI,programa_ingresado,segmento_ingresado);  
            return Prg_setCondicionEmer(val,programa_ingresado,segmento_ingresado);
          }
        }
        
        int get_LimInf_CondE(byte a){
          return 0;  
        }  
        
        int get_LimSup_CondE(byte a){
          return MAX_VALUE_COND+1;  
        }
           
        const TDato ParCondE={
          get_CondE,set_CondE,get_LimInf_CondE,get_LimSup_CondE  
        }; 
      
      
      #endif
  
  		/*  PROGRAMADOR SIMPLE: 1 RAMPA Y 1 MESETA*/
  		/******************************************/
  		#ifdef PROG_SIMPLE_RSTP
  		const TDato ParRSTP_VEL={
          RMP_get_Velocity,RMP_set_Velocity,get_LimInf_TiempoSeg,get_LimSup_TiempoSeg  
        }; 

  		const TDato ParRSTP_SP={
          RMP_get_SetPoint,RMP_set_SetPoint,get_LimInf_SegSP,get_LimSup_SegSP  
        }; 
        
      const TDato ParRSTP_DwellTime={
          RMP_get_DwellTime,RMP_set_DwellTime,get_LimInf_TiempoSeg,get_LimSup_TiempoSeg  
        }; 
  
  		#endif
  		
  #endif
  
/*    COLADA CALIENTE   */
/************************/
#ifdef _COLADA_CALIENTE
    
    /*Potencia*/
    const TDato ParCC_Pot={
          CC_getPotencia,CC_setPotencia,CC_getLimInfPotencia,CC_getLimSupPotencia  
    }; 

		/*Constante*/
		const TDato ParCC_Const={
          CC_getConstanteCorte,CC_setConstanteCorte,CC_getLimInfConstanteCorte,CC_getLimSupConstanteCorte  
    };
		/*Tiempo*/
		const TDato ParCC_TiempoSS={
          CC_getTiempoColada,CC_setTiempoColada,CC_getLimInfTiempoColada,CC_getLimSupTiempoColada  
    };
   /*  Ciclo en Segundos de Potencia Critica y Potencia de Relajo*/
   const TDato ParCC_PotCicle={
    CC_getCicleTime,CC_setCicleTime,CC_getLimInfCicleTime,CC_getLimSupCicleTime 
   };
  /* Tiempo en Segundos en que se puede estar en potencia critica*/
  const TDato ParCC_CritPotTime={
    CC_getCriticalPotTime,CC_setCriticalPotTime,CC_getLimInfCriticalPotTime,CC_getLimSupCriticalPotTime 
   };
  /*  Limite Inferior de Potencia Critica */
  const TDato ParCC_CritPot={
    CC_getCriticalPot,CC_setCriticalPot,CC_getLimInfCriticalPot,CC_getLimSupCriticalPot 
   };
  /*  Limite Superior de la Potencia de Relajo */
  const TDato ParCC_RelaxPot={
    CC_getRelaxPot,CC_setRelaxPot,CC_getLimInfRelaxPot,CC_getLimSupRelaxPot 
   };
 
#endif
/****************************/
/*   GET & SET Parametros   */ 
/****************************/

const TDato ParDoNothing={
  get_Lim_0,EmptyFunction,get_Lim_0,get_Lim_0  
};

const TDato * Parametros[]={
  /*Histeresis*/
  &ParH, 
  /*Histeresis Alarma*/
  &ParHA,
  /*Sensor*/
  &ParSensor,
  /*Decimales*/
  &ParDecimales,
  #ifndef _APARATO_VIEJO
    /*Tcontrol*/
    &ParTipoControl,
  #else
    &ParDoNothing,
  #endif
  /*PeriodoA*/
  &ParPeriodoAlarma,
  /*AutoSintonia*/
  &ParSelfTun,
  #ifdef _PROGRAMADOR
    /*Programa*/
    &ParPrograma,
    /*Segmento*/
    &ParSegmento,
    /*TieSeg*/
    &ParTiempoSegActual,
  #else  
    &ParDoNothing,
    &ParDoNothing,
    &ParDoNothing,
  #endif
  /*SP*/
  &ParSP,
  /*AL */
  &ParAL,
  /*Limite Inferior del SetPoint*/
  &ParLimInfSP,
  /*Limite Superior del SetPoint*/
  &ParLimSupSP,
  /*Reset1*/
  &ParReset,
  /*Filtro*/
  &ParFiltro,
  /*Periodo*/
  &ParPeriodo,
  /*Offset*/
  &ParOffset,
  /*Gan1*/
  &ParGanancia,
  /*Ajuste Cero Termopar */
  &ParAjCeroT,
  /*Ajuste Gan Termopar */
  &ParAjGanT,
  /*Ajuste Cero PT100 */
  &ParAjCeroPT,
  /*Ajuste Gan PT100*/
  &ParAjGanPT,
  /*Ajuste Retransmision Analogico Valor Low*/
  &ParRetLow,
  /*Ajuste Retransmision Analogico Valor Hi*/
  &ParRetHi,
  /*Integral*/
  &ParIntegral,
  /*Derivada*/
  &ParDerivada,
  /*TipoAL*/
  &ParTipoAlarma1,
  /*Talar*/
  &ParTipoAlarma2,
  /*LimPotInf1*/
  &ParLimPotInf,
  /*LimPotSup*/
  &ParLimPotSup,
  /*Tsalcont*/
  &ParTipoSalControl,
  /*Potencia*/
  &ParPotencia,
  /*SetC*/
  &ParSetC,
  /*Variable del Main*/
  &ParVarMain,
  /*Version*/
  &ParVersion,
  /*Id*/
  &ParId,
  /*Ajuste Temperatura Ambiente*/
  &ParAjTempAmb,
  /*  Tiempo de Valvula Proporcional  */
  &ParVpTime,
  /*  Banda Muerta de Valvula Proporcional  */
  &ParVpDeadB,
  #ifdef _PROGRAMADOR	 
    &ParProgConf,
    &ParSegConf,
    #if !defined(prog_viejo)
      &ParTtiConf,
      &ParTiConf,
      &ParTTolGral,
      &ParTolGral,
      &ParCondEGral,
      &ParOnEnd,
      &ParTSeg,
      &ParJumpPrg,
      &ParTTol,
    #else
      &ParDoNothing,
      &ParDoNothing,
      &ParDoNothing,
      &ParDoNothing,
      &ParDoNothing,
      &ParDoNothing,
      &ParDoNothing,
      &ParDoNothing,
      &ParDoNothing,
    #endif
    &ParSegSP,
    &ParTiempoSeg,
    &ParTol,
    &ParCondE,
  #else
    &ParDoNothing,
    &ParDoNothing,
    &ParDoNothing,
    &ParDoNothing,
    &ParDoNothing,
    &ParDoNothing,
    &ParDoNothing,
    &ParDoNothing,
    &ParDoNothing,
    &ParDoNothing,
    &ParDoNothing,
    &ParDoNothing,
		&ParDoNothing,
    &ParDoNothing,
    &ParDoNothing,
  #endif  
    /*programador viejo*/
  #ifdef prog_viejo
    &ParTemp_ini,
  #else
    &ParDoNothing,
  #endif
  #ifdef _COLADA_CALIENTE  
    /*Potencia*/
    &ParCC_Pot,
		/*Constante*/
		&ParCC_Const,
		/*Tiempo*/
		&ParCC_TiempoSS,
    &ParCC_PotCicle,
    &ParCC_CritPotTime,
    &ParCC_CritPot,
    &ParCC_RelaxPot,
 
  #else
    &ParDoNothing,
    &ParDoNothing,
    &ParDoNothing,
    &ParDoNothing,
    &ParDoNothing,
    &ParDoNothing,
    &ParDoNothing,
  #endif
};


  int get_parametro(word par){
    word indice= (par)/4;
    byte elemento= (par)%4;
    
    return get_ValParametro(elemento, Parametros[indice]);
  }

  byte set_parametro(int val,word par){
    word indice= (par-COM_OFFSET)/4;
    byte elemento= (par-COM_OFFSET)%4;
    const TDato * dat= Parametros[indice];
  
    if (val<get_LimInfParametro(elemento,dat) ||
    		val>get_LimSupParametro(elemento,dat)
    )	
      return ERR_VALUE;
    return set_ValParametro(val,elemento,dat);
  }

