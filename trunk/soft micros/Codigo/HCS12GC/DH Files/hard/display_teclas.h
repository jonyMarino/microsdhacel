#ifndef _DISPLAY_TECLAS_H
#define _DISPLAY_TECLAS_H

#define _DPY_SUP			0							// dpy inferior
#define _DPY_INF			1							// dpy superior

#define CHANGE_HD90_TEXT 2000 
#define CANTIDAD_DISPLAYS 4	  
#define MAX_DIGITOS 10 
#define TIME_SCROLL 200
#define DIGITOS 4


void Display_Init(void);  //Inicialización del display con teclado

void PutValLed(bool val,byte num);

void ResetScroll(void);
/*
Borra la pantalla
*/
void Display_clrScreen(void);

void DpyAndSwitch(void);

void AsciiTo7Seg(char* ptrs, byte Num_display,byte Dot);

#endif