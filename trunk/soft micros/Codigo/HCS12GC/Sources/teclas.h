#ifndef _TECLAS_H
#define _TECLAS_H 

#include "PE_Types.h"

#ifdef DEBUG
#include "Mydefines.h"
#endif

/* definiciones del teclado */
#define KEY_RAMPA_INI	80 /*A los cuantos ingresos(la primera vez) iguales se repite la salida para ese pulsador*/
#define KEY_RAMPA_FIN	0  /*Maxima velociadad de ingresos iguales a los que se repite la salida para ese pulsador*/
#define KEY_DELTA	1  /*Variacion de velociadad una vez realizada la salida*/

/* Posicion de cada tecla*/
#if defined( DEBUG) && !defined(_DISPLAY_2x4)
  #define KEY_NULL		0X00
  #define KEY_UP      0x04
  #define KEY_DOWN    0x02
  #define KEY_RESET   0x10
  #define KEY_ENTER   0x01
#else

  #define KEY_NULL		0X00
  #define KEY_UP      0x04
  #define KEY_DOWN    0x08
  #define KEY_RESET   0x10
  #define KEY_ENTER   0x02

#endif

#define CANTIDAD_TECLAS 4      /*Cantidad de pulsadores/teclas que se leen del intrumento*/
#define CANTIDAD_VALIDACIONES 8 /*Cantidad de ingresos iguales que hace falta para validar
                                o asegurar que una tecla fue presionado(si es 0 no corrobora)*/
					
void Teclas_Init(void);
void Switches(byte Pulsador); // Pulsador: posicion de la tecla

char get_key(void);

/*  Avisa si paso el tiempo de espera de tecla */
bool Teclas_TimePass(void);

#endif