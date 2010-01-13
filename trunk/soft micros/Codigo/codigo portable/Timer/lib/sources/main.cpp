#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
/*$AsmDecl$*/


void main(void) {
  /* put your own code here */
  /*$XGATECall$*/
	EnableInterrupts;
/*$AsmCall$*/

  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
