#ifndef Boxes_H
#define Boxes_H


/* archivos include */
#include "display.h"
#include "cnfbox.h"
#include "PE_Error.h"
#include "PWM.h"
#include "TmDt1.h"
#include "Adquisidor.h"
#include "IFsh10.h"
#include "Timer.h"

void Boxes_Init(void);

void ProcesarBox(byte tecla);

bool Box_is_actual(PunteroF ppf); // recibe la direccion de algun Box y devuelve TRUE si es el actual, FALSE en caso contrario

void ProcTextual1(Textual1 * text_box);

void ProcTextual2(Textual2 * text_box);

void ProcTextual3(Textual3 * text_box);

void ProcTextual4(Textual4 * text_box);

void ProcTextJumpCond(TextualJumpCond * text_box);

void ProcNumerico1(Numerico1 * num_box);

void ProcNumerico2(Numerico2 * num_box);

void ProcNumerico3(Numerico3 * num_box);

void ProcNumerico4(Numerico4 * num_box);

void ProcNumJumpCond(NumericoJumpCond * num_box);

void ProcTitle(Titulo * tit_box);

void set_proximo(PunteroF proximo);

void Box_set_new(PunteroF ppf); // Equivalente a  set_proximo() pero no hace nada si ya se encuentra en el box correspondiente

void boxes_refresh_value(void);

/* Procesador de Numerico Read Only Con Salto Condicional*/
/*********************************************************/
void ProcNumRO_JmpCond(NumRO_JmpCond * num_box);

void ProcTitleProg(Titulo * tit_box);

void CondEGralHandler(Textual1 * text_box);

void NumExpoHandler(void);

void TieSegHandler(Numerico1 * num_box);

void ABHandler(Numerico1 * num_box);

void ABAHandler(Numerico1 * num_box);

void CodHandler(Numerico2 * num_box);

void ProgramaHandler(Numerico1 * num_box);

void SegmentoHandler(Numerico1 * num_box);

void Num_realtime_Handler(void);

void DiaHandler(void);

void HoraHandler (void);

void NumProgHandler(Numerico1 * num_box);

void ProcNumJmpCondProg(NumericoJumpCond * num_box);

void ProcTxtJmpCondProg(TextualJumpCond * txt_box);


void MainHandler(NumericoJumpCond * num_box);

void set_MainText(const char * str);  /* Para poner Textos en el Display inferior*/


///Funciones de Main///
typedef enum{
  TEXT_FLASHING,
  TEXT_CONTINUOS
}T_MainTextMode;

void set_MainStaticText(const char * str);

void Main_setTextWMode(const char * str,T_MainTextMode mod);




#endif