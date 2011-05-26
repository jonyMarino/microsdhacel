#include "Set.hpp"

bool Set::add(void *dato){
  if(contains(dato))
    return FALSE;
  LinkedList::add(dato);
  return TRUE;
}

bool Set::aniadir(void *dato){
  if(contains(dato))
    return FALSE;
  LinkedList::aniadir(dato);
  return TRUE;
}