#include "Control.h"

/*
** ===================================================================
**     Method      :  Cntrl_getSP / Cntrl_setSP
**     Description :  Set Point operativo
** ===================================================================
*/
/*int Cntrl_getSP(void * self){
  struct Control * _cont = self;
  struct TControl ** Vtable = self;
  return (** Vtable).get_SetPoint(_cont);
  
}  */

uchar Cntrl_setSP(void * self,int val){
  struct Control * _cont = self;
  struct TControlClass ** Vtable = self;
  return (** Vtable).set_SetPoint(_cont, val);
  
}
