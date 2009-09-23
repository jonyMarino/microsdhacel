#include "Cpu.h"
#include "Masks.h"
#include "BoxesStruct.h"
#include "vx2.h"
#include "IFsh10.h"
#include "Mydefines.h"
#include "Rele1.h"
#include "Rele2.h"
#include "FormasConteo.h"

#ifdef TEST_CUENTA_CALCULADA
  #undef vx1_GetVal
  #undef vx2_GetVal
  #include "CuentaCalculada.h"
#endif

#pragma CONST_SEG ROM_BYTE
volatile const TAccionSP AccionSPP=ACCION_AUTO_RESET;
volatile const TAccionSP AccionSPA=ACCION_AUTO_RESET;
volatile const TModoSP_Auxiliar ModoSP_Auxiliar=MODO_SPA_TOT_ON_SPP;
volatile const TModoCuenta ModoCuenta=MODO_UP;
#pragma CONST_SEG DEFAULT

extern byte ContFlags;
extern volatile const TModoCuenta ModoCuenta;
extern volatile const long SP_Principal;
extern volatile const long FactorEscala[2];
extern long PreTotalizador;
extern long ValProc;
extern bool led[2];
extern volatile const ModoSetPoint[2];
extern volatile const long SP_Auxiliar;

void StopCmpValSPA(void);
void ContinueCmpValSPA(void);
/*
** ===================================================================
**     Method      :  FormasConteo_Contador (bean PE_Timer)
**
**     Description :
**         Esta funcion es para un contador UP-Down común.
** ===================================================================
*/
extern long TotCuenta;
extern long TotOnSPP;
extern byte DebounceTime;
extern long Cuenta;
extern byte Sensor[1];
char flag_TotCuSetUP_SPA;


/***********Cuenta****************/
void FormasConteo_Contador(void){
  if(!(ContFlags&CNT_STOP_MASK)&& !(Sensor[0]==MICROSWITCH && DebounceTime)){			  
    DebounceTime=DEBOUNCE_TIME ;
    (!vx2_GetVal())?Cuenta++:Cuenta--; 
  }
}

void FormasConteo_RPM(void){
  //   = FreeCounter_GetTimeSec(&Cuenta);
    (!vx2_GetVal())?Cuenta++:Cuenta--; 
}



long Cnt_getCuenta(void){
long tmp;  
		  Cpu_DisableInt();
		  tmp = Cuenta;
		  Cpu_EnableInt();
		  return tmp;
}

long Cnt_getCuentaEscalada(void){
		  return Cnt_getCuenta()*(FactorEscala[0] / 10000.0);
}


void Cnt_setCuenta(long val){
  Cpu_DisableInt();
  Cuenta=val; 
  Cpu_EnableInt(); 
}

void ResetCuenta(void){
      if(!(ContFlags&TOT_CNT_STOP_MASK))
        PreTotalizador+=Cnt_getCuenta();
      else{
        TotCuenta=0;
        PreTotalizador=0;
      }
      if(ContFlags&TOT_ON_SPP_STOP_MASK)
        TotOnSPP=0;
      
	    Cnt_setCuenta(0);
	    ValProc=0;
	    ContFlags=0;
	    #ifdef TEST_MODE
      Entries=0;
      PreCuenta=0;
      #endif
	    Rele1_PutVal(led[0]=(ModoSetPoint[0]==EXCESO)?0:1);
	    Rele2_PutVal(led[1]=(ModoSetPoint[1]==EXCESO)?0:1); 
}

/*  Modo de SP Auxiliar */
TModoSP_Auxiliar Cnt_getModoSPaux(void){
  return ModoSP_Auxiliar; 
}

byte  Cnt_setModoSPaux(TModoSP_Auxiliar mod){
  return IFsh10_Setbyte((word)&ModoSP_Auxiliar,mod);
}

long Cnt_getValCmpSPA(void){
  switch(ModoSP_Auxiliar){
    case MODO_SPA_CUENTA:{
     long tmp; 
     tmp=Cnt_getCuenta();
     if(ModoCuenta==MODO_DOWN)
      return SP_Principal-tmp;
     return tmp;
    }
    case MODO_SPA_TOT_CUENTA:
      return TotCuenta;
    case MODO_SPA_TOT_ON_SPP: 			 
      return TotOnSPP;
  }
}

void Cnt_clrValCmpSPA(void){
  switch(ModoSP_Auxiliar){
    case MODO_SPA_TOT_CUENTA:
      TotCuenta=0;
      PreTotalizador=0;
      ContFlags&= ~TOT_CNT_STOP_MASK;
      //PreTotalizador-=Cnt_getCuenta();
      break;;
    case MODO_SPA_TOT_ON_SPP: 
      TotOnSPP=0;
      ContFlags&= ~TOT_ON_SPP_STOP_MASK;
      break;
  }

}

void StopCmpValSPA(void){
   switch(ModoSP_Auxiliar){
    case MODO_SPA_TOT_CUENTA:
        ContFlags|= TOT_CNT_STOP_MASK;
        if(TotCuenta>=SP_Auxiliar){
          //PreTotalizador = SP_Auxiliar;
          flag_TotCuSetUP_SPA = 1;
        }
        else {
          flag_TotCuSetUP_SPA = 0;
          //PreTotalizador = 0;
        }
      break;
    case MODO_SPA_TOT_ON_SPP:
        ContFlags|= TOT_ON_SPP_STOP_MASK;
        if(TotOnSPP>=SP_Auxiliar) 
        flag_TotCuSetUP_SPA = 1;
      else flag_TotCuSetUP_SPA = 0;  
      break;     
   }
}


void ContinueCmpValSPA(void) {         
  switch(ModoSP_Auxiliar){
    case MODO_SPA_TOT_CUENTA:
      if(TotCuenta>SP_Auxiliar) 
        flag_TotCuSetUP_SPA = 1;
      else flag_TotCuSetUP_SPA = 0; 
      break;
    case MODO_SPA_TOT_ON_SPP:
       if(TotOnSPP>SP_Auxiliar) 
        flag_TotCuSetUP_SPA = 1;
      else flag_TotCuSetUP_SPA = 0;  
      break;     
   }


}


void Cnt_OnValEqualToSPA(void){
  if(ModoSP_Auxiliar!=MODO_SPA_CUENTA)	 
  	 switch(AccionSPA){
  	  case ACCION_CONTINUE:
  	   // ContFlags&=~SPA_MASK;
  	    ContinueCmpValSPA();
  	    break;
      case ACCION_STOP:
        StopCmpValSPA();
        //flag_TotCuSetUP_SPA = 0;
        break;
      case ACCION_AUTO_RESET:
  	   Cnt_clrValCmpSPA();
  	   ContFlags&=~SPA_MASK;
  	   flag_TotCuSetUP_SPA = 0;
  	   break;
  	  
  	 }
}

/*  Set Point Principal */


/*  On new Cuenta */
