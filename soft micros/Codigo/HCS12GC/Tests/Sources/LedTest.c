/* MODULE LedTest*/

#include "Bits2ULN.h"
#include "Bits5ULN.h"
#include "Display1.h"
#include "LedTest.h"

#define SELECT_LEDS 0x80


byte leds=0;

void set_Led(byte num){
  Display1_PutVal(0);	 //PTA
  bits2ULN_PutVal(SELECT_LEDS);		// PTJ
  
  leds|=(1<<num);

	bits5ULN_PutVal(leds); 	 //PTM
}

void Clr_Led(byte num){

  leds&=~(1<<num);
  
  bits5ULN_PutVal(leds); 	 //PTM
}

byte get_Led(byte num){
  return (leds&(1<<num));
}

