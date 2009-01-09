#ifndef _UTIL_VISTA_H
#define _UTIL_VISTA_H

#define ADAPTAR_BYTE_A_INT_GET(f) \
  int f##Vista(void * obj){       \
    return f(obj);                \
  }

#define ADAPTAR_BYTE_A_INT_SET(f) \
  byte f##Vista(void * obj,int val){       \
    return f(obj,val);                \
  } 
  
  
#endif