
#include "PWMHard23.hpp"
#include "PWMHard.hpp"

#pragma CONST_SEG PARAMETERS_PAGE
volatile const TConfPWM pwmconf23={0};
#pragma CONST_SEG DEFAULT

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

void PWMHard23::setPotencia(unsigned int potencia) {
  if(PWME_PWME3){		 /* PWM?*/    
    setDuty(RefPWM23,potencia);
  }
  else{
    if(potencia==0)
      clrReg8Bits(PTT, 8);               /* PTT3=0 */
    else
      setReg8Bits(PTT, 8);               /* PTT3=1 */ 
  }
  Salida_setPotencia(potencia);
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
  return PTT_PTT3;
}