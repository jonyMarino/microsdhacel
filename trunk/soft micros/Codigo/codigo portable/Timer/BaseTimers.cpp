#include "BaseTimers.hpp"
#include "Timer.hpp"



void BaseTimers::incrementar(unsigned int ms){
  cuenta+=ms;
}

bool BaseTimers::moveOut(void * timer){
  byte err;
  lockInc();
  err = LinkedList::moveOut(timer);
  unlockInc();
  return err;
}


void BaseTimers::actualizarTimers(void){
  LinkedList::LinkedListIterator iterator;
  
  linkedListIterator(&iterator);
  
  while(iterator.hasNext()){
    ((Timer *)iterator.next())->comparar();      
  }
}

unsigned long BaseTimers::getCuenta(){
  unsigned long cuentatmp;
  lockInc();
  cuentatmp = cuenta;
  unlockInc();   
  return cuentatmp;
}
