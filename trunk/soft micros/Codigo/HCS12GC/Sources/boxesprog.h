#ifndef _BOXES_PROG_H
#define _BOXES_PROG_H 

#pragma CONST_SEG DEFAULT 
#pragma STRING_SEG DEFAULT

//extern const Titulo Programas;
extern const Numerico1 Program;
extern const NumericoJumpCond Segmento;
#ifdef prog_viejo
  extern const NumericoJumpCond Temp_i;
#endif

  #ifdef prog_viejo
  /// Son los numeros que se muestran en los boxes ej 2E 3
  void Reset_ProgSegMostrados(void);
  byte ConfPrg_getSegMostrado(void);
  byte ConfPrg_getProgMostrado(void);
  #endif
#endif