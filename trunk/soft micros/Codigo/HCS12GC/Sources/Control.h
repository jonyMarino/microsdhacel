#ifndef _CONTROL_H
#define _CONTROL_H

#include "PE_Types.h"
#include "Object.h"
#include "getter.h"

struct TControlClass{
  struct GetterClass super;
//public:
  uchar (*set_SetPoint)(void *,int);
//protected:
  void (*OnSensNewVal)(void*);	 // evento ante un valor nuevo de sensor            
};

typedef enum{
  CNTR_ONOFF,
  CNTR_PID
}T_TipoControl;

struct Control{
  struct TControl *  _control;
};


#define _CNTRL_setSP(control,val) \
          (*((*(struct TControl**)control)->set_SetPoint))(control,val)


/*
** ===================================================================
**     Method      :  Cntrl_getSP / Cntrl_setSP  
**     Description :  Set Point operativo
** ===================================================================
*/
//int Cntrl_getSP(void * self);
uchar Cntrl_setSP(void * self,int val);


#endif

