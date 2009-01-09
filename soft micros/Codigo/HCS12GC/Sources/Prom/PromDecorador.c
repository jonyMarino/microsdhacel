#include "PromDecorador_protected.h"

void PromDecorador_constructor(void *self,struct PromBkp * promBkp){
  struct PromDecorador * p = self;
  p->promBkp = promBkp;
  
}

void PromDecorador_defConstructor(void *self, va_list * args){
  PromDecorador_constructor(self, va_arg(*args,void*));
}