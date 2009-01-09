#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "PE_Types.h" 

void ResetScroll(void);

void DpyAndSwitch(void);

#ifdef jony_28_06
void PasarASCII(const char *PtrText,byte Num_display);
#endif

void Pasar_Numero(int valor,byte Num_display, byte Dot);

void Pasar_Numero_Expo(int valor,byte Num_display, byte Dot);

#endif

