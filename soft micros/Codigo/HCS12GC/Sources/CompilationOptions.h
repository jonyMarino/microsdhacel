#ifndef _COMPILATION_OPTIONS_H
#define _COMPILATION_OPTIONS_H

#include "Mydefines.h"

#ifdef _PROGRAMADOR
  #define _PROG 1
#else
  #define _PROG 0
#endif

#if _TIEMPO_AD_EN_MILISEGUNDOS==250 /*  Un ciclo de AD en 1 segundo*/
  #define AD_T 0 
#elif _TIEMPO_AD_EN_MILISEGUNDOS==500 /*  Un ciclo de AD en 1 segundo*/
  #define AD_T 1
#elif _TIEMPO_AD_EN_MILISEGUNDOS==1000 /*  Un ciclo de AD en 1 segundo*/
  #define AD_T 2
#elif _TIEMPO_AD_EN_MILISEGUNDOS==2000 /*  Un ciclo de AD en 1 segundo*/
  #define AD_T 3
#endif

#ifdef DOBLE_SET_POINT 
  #define _DSP 1
#else 
  #define _DSP 0
#endif  

#ifdef _ADQUISIDOR
  #define _ADQ  1
#else
  #define _ADQ  0
#endif  


 
#define _COMP_OPTIONS	(CANTIDAD_CANALES-1) /*2bit*/     \
                     | CANTIDAD_SAL_CONTROL<<2/*3bit*/| AD_T<<5/*3 bit*/ \
                     | CANTIDAD_SAL_ALARMA<<8/*3bit*/ \
                     | _DSP << 11 /* 1 bit */| _ADQ<<12/*1 bit*/
#endif 