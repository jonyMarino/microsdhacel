#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "PE_Types.h" 

#define DISPLAY1 0
#define DISPLAY2 1
#define DISPLAY3 2
#define DISPLAY4 3

#define NO_DIGIT 127

void DpyAndSwitch(void);

//void AsciiTo7Seg(byte Num_display);

void PasarASCII(char *PtrText,byte Num_display);

void Pasar_Numero(long valor,byte Num_display);


#endif

