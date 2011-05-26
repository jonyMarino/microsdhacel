#include <hidef.h>      /* common defines and macros */
#include <assert.h>
#include "derivative.h"      /* derivative-specific definitions */
#include "timer_interrupt.h"
#include "Termometro.hpp"
#include "OutputStream.hpp"
#include "Cpu.h"
#include "WDog1.h"
#include "Timer/Timer.hpp"
#include "Timer/interrup_1ms_40ms/BaseTimers_1ms_40ms.hpp"
#include "Memoria/Prom/Flash/FlashBkpMitad/FlashBkpMitad.hpp"
#include "PropNumLFPF.hpp"
#include "modbus.hpp"
#include "SDFat.hpp"
#include "SPI.hpp"


#pragma CONST_SEG DEFAULT


class Init{
  public:
  Init(){  
    Timer::setBaseTimerDefault(*BaseTimers_1ms_40ms::getInstance());
  }
}ini;


 
PlataformaEmbedded plataforma; 

SPI spi;

class SDPresent: public BitIn{
  public:
    SDPresent(){
      DDRB_BIT3 = 1;  //PTB bit3 es entrada
    }
    bool getBit(){
      return PORTB_BIT3;
    }
}sdPresent;

void main(void) {
    PE_low_level_init();
  
    byte i;
    
    

    SDFat sd(spi,sdPresent);
    Timer timer(2000);
    
    for(;;){ 
        
        
        plataforma.mainLoop();
        
        if(timer.isFinished()){
            byte error;
            byte str[5];
            str[0]=  i%10+'0';
            str[1]=(i/10)%100+'0';
            str[2]=(i/100)%1000+'0';
            str[3]=',';
            str[4]=0;
            
            timer.restart();
            i++;
            error=sd.fileOpen((VUINT8*)"LOG.TXT",MODIFY);
            sd.fileWrite(str,4);
            sd.fileClose();
        }
    }
    
  
  /* please make sure that you never leave main */
}
 