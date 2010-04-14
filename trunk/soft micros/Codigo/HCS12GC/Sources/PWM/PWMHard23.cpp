
#include "PWMHard23.hpp"
#include "PWMHard.hpp"


#pragma DATA_SEG PWM_HARD_23_DATA                                            
#pragma CODE_SEG PWM_HARD_23_CODE                     
#pragma CONST_SEG PWM_HARD_23_CONST   

static const int periodos[]={   
  25000,											//100 ms
  50000,											//200 ms
  1250 ,											//500 ms
  2500 ,											//1s
  5000 ,											//2s
  12500,											//5s
  25000, 											//10s
  50000,											//20s
  31250,											//50s
  1250   											//5ms
};

void PWMHard23::PWMHard23(struct ManejadorMemoria &_manejadorMemoria,const TConfPWM &_conf):PWMHard(_manejadorMemoria,_conf){
  CONTROLADOR_PWM_INIT(2,3);
  													 
  PWMPRCLK_PCKB = 6; 		// dividido 64
   
 // setReg8Bits(DDRT, 8);
  
  #ifdef __MODRR
  setReg8Bits(MODRR, 8);  //cablear al puerto T 
  setReg8Bits(DDRT, 8);
  #else
  setReg8Bits(DDRP, 8);
  #endif
}    

void PWMHard23::setPotenciaGuardada() {
  unsigned int potencia = getPotencia();
  if(PWME_PWME3){		 /* PWM?*/    
    setDuty(RefPWM23,potencia);
  }
  else{
    if(potencia==0)
      #ifdef __MODRR
      clrReg8Bits(PTT, 8);//8              /* PTT3=0 */
      #else
      clrReg8Bits(PTP, 8);//8 
      #endif
    else
      #ifdef __MODRR
      setReg8Bits(PTT, 8);//8            /* PTT3=1 */
      #else
      setReg8Bits(PTP, 8);//8
      #endif 
  }
}

void PWMHard23::setTipoSalida(TipoSalida tipoSalida){
  PWME_PWME3 = (tipoSalida==SALIDA_ONOFF)?0:1;
}

TipoSalida PWMHard23::getTipoSalida(){
 return (PWME_PWME3)?SALIDA_PROPORCIONAL:SALIDA_ONOFF;
}

unsigned char PWMHard23::setPeriodo(TPeriod period){
 unsigned char err;
  if(period<0 || period>PWM_MAX_VALUE_PERIODS)
    return ERR_VALUE; //error
  err= setPeriodoConfiguracion(period);
  if(!err){
    TPeriod tperiodo = period;
    switch(tperiodo){
      case PWM_100ms:
      case PWM_200ms:
      case PWM_Anl:
        PWMCLK_PCLK3 = 0;
        break;
      default:
        PWMCLK_PCLK3 = 1; 
        if(tperiodo == PWM_50sec)
          PWMSCLB = 200;
        else
          PWMSCLB = 50;    
    }
    
      
    
    PWMPER23 = periodos[period];
  }
  return err;
}

bool PWMHard23::getEstadoSalida() {
  #ifdef __MODRR
  return PTT_PTT3;               /* PTT3=0 */
  #else
  return PTP_PTP3; 
  #endif
}