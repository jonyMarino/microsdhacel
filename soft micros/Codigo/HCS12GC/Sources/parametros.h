#ifndef _PARAMETROS_H
#define _PARAMETROS_H 

#include "PE_Types.h"

#define NO_FUNCTION NULL

/* definicion de la estructura de dato de los Boxes*/         
/*******************************************************/
typedef struct{
  int (*get)(byte);			/* Funcion a ejecutar para obtener el valor del parámetro */
  byte (*set)(int,byte);			/* Funcion a ejecutar para setear un valor del parámetro, retorna error en la escritura*/
  int (* get_lim_inf)(byte);   /* Funcion a ejecutar para obtener el limite inferior del parámetro */
  int (* get_lim_sup)(byte);		/* Funcion a ejecutar para obtener el limite inferior del parámetro */
}TDato;


/*typedef struct{
  TDato functions;
  int * dato;
}TDato_w_val;

typedef struct{
  TDato_w_val Dato_w_val;
  int LimInf;
  int LimSup;
}TDato_w_val_lim;
	 */
//byte Escribir(TDato * sDato,int valor);

///Utilitarias para definir el objeto

int get_Lim_min_display(byte a);
int get_Lim_0(byte a);
int get_Lim_max_display(byte a);
void EmptyFunction(void);
////////////////////////////////////////

int get_parametro(word par);
byte set_parametro(int val,word par);

#define get_ValParametro(ne,dat)    ((* (dat->get))(ne)) 
#define	get_LimInfParametro(ne,dat) ((* (dat->get_lim_inf))(ne))
#define	get_LimSupParametro(ne,dat) ((* (dat->get_lim_sup))(ne))

#define set_ValParametro(val,ne,dat)    ((* (dat->set))(val,ne))

/**********************/
/*    PROGRAMADOR     */ 
/**********************/
int get_Tti(byte a);
/*  Tipo de tolerancia general  */
int get_TTolGral(byte a);
/*  Condicion de Emergencia general  */
int get_CondEGral(byte a);
/*  Tipo de Segmento*/
int get_TSeg(byte a);
/*  Tipo de tolerancia  */
int get_TTol(byte a);

  /*  Para programador viejo*/
  void En_ProgConf(void);
  /*  Programa Ingresado  */  
  int get_ProgConf(byte a);
  byte set_ProgConf(int val,byte a);
  /*  Segmento Ingresado  */
  int get_SegConf(byte a);
  byte set_SegConf(int val,byte a);
  /*  Condicion de Emergencia */
  int get_CondE(byte a);
  
#endif