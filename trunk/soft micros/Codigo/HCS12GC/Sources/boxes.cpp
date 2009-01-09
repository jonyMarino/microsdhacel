/* archivos include */
#include "display.h"
#include "PE_Error.h"
#include "PWM.h"
#include "TmDt1.h"
#include "Adquisidor.h"
#include "IFsh10.h"
#include "cnfbox.h"
#include "Programador.h"
#include "Timer.h"
#include "Sensores.h"
#include "PTSL.h"
#include "cnfbox.h"
#include "boxes.h"
#include "boxesprog.h"


#pragma CODE_SEG DEFAULT
#ifdef pirani
static const char UF[]="UF  ";
static const char OF[]="OF  ";
#else
static const char UF[]=" UF ";
static const char OF[]=" OF ";
#endif
#pragma DATA_SEG DEFAULT
char main_text[5]="St  ";
bool show_main_text;

#pragma CONST_SEG DEFAULT
//extern const byte Pot_2[];
extern const int div_dec[];



extern byte b,d;
byte Tecla;
extern bool Flag1;
extern dword St_Counter[NUM_SALIDAS];
extern byte St_Step[NUM_SALIDAS];

							

extern int duty_cont_ch[4];

extern long suminteg[CANTIDAD_CANALES];
long auvis1;
extern int vxalar;
extern bool SaveNow;

/* variables de uso temporal por los boxes cuando se activan */
int Valor_Tmp;				// Buffer del parametro procesado
bool save_parametros=FALSE;	/* Ordena salvar el valor en la ram para copy a eeprom cuando set*/
bool save;
bool FstTime=TRUE;	/* set cuando se ejecuto al menos una vez el procesador */
#ifdef programador
static enum {NOPROGRAMA,PROGRAMA}BoxAnterior; // Para saber desde donde se entro al BOx de Segmento
#endif

/* Drivers para simular el hardware */
/************************************/
extern byte DotNum[CANTIDAD_DISPLAYS];			/* punto decimal a encender */


//////////////Funciones internas//////////////////////
void Exit(void);					 // Salir a pantalla principal
void Salir_num(void);	 // Salir por toque rapido o sostenido en pantalla numérica
void procesar_up_down(byte tecla,const TDato * ptrVar,int * valor_tmp);
PunteroF procesar_sig_parametro1(byte tecla,TSiguientes * siguiente);
PunteroF procesar_sig_parametro2(byte tecla,TSiguientes * siguiente);

#ifdef adquisidor
void A_Adquiriendo (void); // Accion al poner si o no en el adquisidor
#endif

byte Escribir(TDato * sDato,int valor){
  byte err;
  
  if(*(sDato->Inf)>valor || *(sDato->Sup)<valor) return ERR_VALUE;  /* Checkeo Rangos*/
  if(sDato->Fdir!=NULL){																					  /*Escribo*/
    if((word)sDato->Fdir<RAM_END && (word)sDato->Fdir>=RAM_START)//RAM
      *(sDato->Fdir)=valor;
    else if((word)sDato->Fdir>=FLASH_PARAMETROS_START){    //ROM
      err=EscribirWord((word)sDato->Fdir,valor);
      if(err)
        return err; 
    }
    else return ERR_RANGE; 
  }
  if (sDato->OnWrite==NULL)
    return ERR_OK;
  return (*(sDato->OnWrite))(valor, sDato->chan);		/*Ejecuto Accion*/
};


/* Procesadores de los boxes */
/*****************************/

/* Procesador de Base box */
/**************************/
void BoxProc(TBox * box)
{
	if (FstTime){					// es la primera vez que ingresa??
		FstTime=FALSE;			// sacar primera vez
		PasarASCII(box->TxtDpy,0); //mostrar display superior	
	};	
}