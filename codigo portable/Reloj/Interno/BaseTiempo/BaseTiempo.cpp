#include "BaseTiempo.hpp"

/*
** ===================================================================
**     Method      :  BaseTiempo_constructor (bean TimeDate)
**
**     Description :
** ===================================================================
*/
BaseTiempo::BaseTiempo(word anio,byte mes,byte dia,byte hora,byte min,byte segs):FechaIncrementable(anio,mes,dia,hora,min,segs),timer(1000,incUnSegundo,this)
{ 
}

/*
** ===================================================================
**     Method      :  BaseTiempo_incUnSegundo
**
**     Description :
** ===================================================================
*/
void BaseTiempo::incUnSegundo(void * _self){
  BaseTiempo * self = (BaseTiempo *) _self;
  self->incrementar(1);
}





