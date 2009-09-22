#ifndef _PROGRAMADOR_H
#define _PROGRAMADOR_H
#include "PE_Types.h"
#include "Mydefines.h"

#define MAX_PROGRAMAS 10
#define MAX_SEGMENTOS 24

#define TAMANIO_SEGMENTO 5

typedef struct{
  int tipo_segmento;
  byte condicion_emer;
  byte tipo_tolerancia;
  int temperatura_f;
  word tiempo;  
  int tolerancia;
  } TSegmentos;		//10 bytes(debe ser par)

#define TAMANIO_GENERAL 4 //Sin el Cant_Seg que se graba aparte
typedef struct{
  bool tipo_temperatura_inicial;
  byte tipo_tolerancia;
  int temperatura_inicial;  
  int tolerancia;					 
  int condicion_emer;
  }Tinfoprograma;  //8 bytes (debe ser par)
  
typedef struct{
 Tinfoprograma Gral;
 TSegmentos Segmento[MAX_SEGMENTOS];
 byte nada[8]; //debe haber por lo menos un nada declarada para que se ponga en End en el segmento 26
}TProgramas;		 //sizeof(TProgramas)= 256 bytes

#define next_vel next_tiempo
#define velocidad tiempo
#define ciclos tiempo 

#define sub_programa temperatura_f  

void A_Programa(void);

void A_Ingreso_Segmento(void);

void A_Segmento(void);

void A_Condicion_Emergencia_General(void);

void ActualizarSetPointPrograma(byte canal);

void runPrograma(byte canal,byte programa, byte Segmento);

void ReestablecerPrograma(byte canal);

#define GuardarPrograma() (void)WriteArray(FLASH_APAGADO_START,0, (7+3*MAX_PROGRAMAS)*CANTIDAD_SAL_CONTROL, (word*)ProgramaActual)
#endif