#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "PE_Types.h" 
#include "display_teclas.h"

#define MAX_NUM_DISPLAY 9999
#define MIN_NUM_DISPLAY -1999

void PasarASCII(const char *PtrText,byte Num_display);

void Pasar_Numero(int valor,byte Num_display, byte Dot);
/*
** =====================================================================
**    Function      :  PasarHexaNum 
**    Description :    Muestra numero en hexa
** =====================================================================
*/
void PasarHexaNum(word valor,byte Num_display);

void Pasar_Numero_Expo(int valor,byte Num_display, byte Dot);

void Pasar_NumeroNatural_Expo(word valor,byte Num_display, byte Dot);

void Pasar_NumeroGrande(long val,byte Num_display, byte Dot);

#endif

