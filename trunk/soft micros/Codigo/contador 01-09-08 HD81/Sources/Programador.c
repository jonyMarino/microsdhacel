#include "Programador.h"
#ifdef programador
#include "display.h"
#include "BoxesStruct.h"
#include "IFsh10.h"

#if End !=0
  #error se va a tener que inicializar los programas en nada[0]=End
#endif 

#define  segmento  Programa[programa_ingresado].Segmento[segmento_ingresado]
#define  general   Programa[programa_ingresado].Gral 

static enum {NOPROGRAMA,PROGRAMA}BoxAnterior; // Para saber desde donde se entro al BOx de Segmento

extern word * datos_grabar;			//Variables usadas para grabar en FLASH//
extern word direccion_grabar;		//Variables usadas para grabar en FLASH//
extern byte cant_datos_grabar;  //Variables usadas para grabar en FLASH//
extern bool save_array;					//Variables usadas para grabar en FLASH//
extern byte indice_datos[2];
Tinfoprograma BufferGeneral;		//Contiene los datos a grabar
TSegmentos BufferSegmento;			//Contiene los datos a grabar

extern int ValFinal[4]; //Variable Proceso

bool pendiente_negativa; //Determina la pendiente para el tipo rampa velocidad

/////Guardar ante corte//////
byte ProgramaActual[CANTIDAD_SAL_CONTROL];				//Programa actualmente corriendo, es distinto de PRom[R_Programa], ya que el tipo de segmento JUMP lo puede modificar
byte SegmentoActual[CANTIDAD_SAL_CONTROL];				//Segmento corriendo del programa actual,
dword SegundosSegmento[CANTIDAD_SAL_CONTROL];			//Segundos transcurridos en el segmento actual
int SetPointPrograma[CANTIDAD_SAL_CONTROL];				//Set Point del Programa actual
int TemperaturaAnterior[CANTIDAD_SAL_CONTROL];		//Temperatura que habia al comenzar el segmento

struct{																						//Esta estructura contiene la info para recuperar el programa luego de un JUMP (Se verifica ante un END)
byte Programa;																		//(Programa al cual volver)+1, si es cero no se vuelve a ningun programa. Se verifica en End
byte Segmento;																		//Segmento al cual volver->Es un Jump
byte Ciclos;																			//Ciclos de repeticion del programa. Se ejecuta en End
}ProgramReturn[CANTIDAD_SAL_CONTROL][MAX_PROGRAMAS];
////////////////////////

TSegmentos SegVal[CANTIDAD_SAL_CONTROL];					//Valores temporales para correr el segmento actual

const TProgramas  Programa[MAX_PROGRAMAS] @(FLASH_PROGRAMADOR_START)={		 //Programas guardados en FLASH
0,  //tipo_temperatura_inicial
1,  //tipo_tolerancia
0,  //temperatura_inicial
0,  //tolerancia
rP,  //condicion_emer
//Tipo    ce  tt  ºC    tempo tol
  rMPt,   0,  0,   10,    1,  0,
  JMP,    0,  0,    1,    2,  0,
  rMPt,   0,  0,    0,    1,  0,
  End ,   0,  0,	200,		1,  0,
  rMPt,   0,  0,   50,		1,  0,
  End ,   0,  0,    0,    0,  0,
  End ,   0,  0,    0,    0,  0,
  End ,   0,  0,    0,    0,  0,
  End ,   0,  0,    0,    0,  0,
  End ,   0,  0,    0,    0,  0,
  End ,   0,  0,    0,    0,  0,
  End ,   0,  0,    0,    0,  0,
  End ,   0,  0,    0,    0,  0,
  End ,   0,  0,    0,    0,  0,
  End ,   0,  0,    0,    0,  0,
  End ,   0,  0,    0,    0,  0,
  End ,   0,  0,    0,    0,  0,
  End ,   0,  0,    0,    0,  0,
  End ,   0,  0,    0,    0,  0,
  End ,   0,  0,    0,    0,  0,
  End ,   0,  0,    0,    0,  0,
  End ,   0,  0,    0,    0,  0,
  End ,   0,  0,    0,    0,  0,
  End ,   0,  0,    0,    0,  0,
  End,0,0,0,0,0,0,0, //nada
0,
1,
10 ,
0,
rP,
//Tipo    ce  tt  ºC    tempo tol
  MSt ,   0,  0,    0,    1,  0,
  rMPV,   0,  0,    0,  100,  0,
  MSt,    0,  0,    0,    1,  0,
  rMPt,   0,  0,   10,    1,  0		 
};

// VARIABLES QUE UTILIZAN LOS BOXES
int	 programa_ingresado, segmento_ingresado, temperatura_inicial,  tipo_segmento, temperatura_f,
	   tiempo, tolerancia,tolerancia_gral, condicion_emer,condicion_emer_gral,tipo_tolerancia,tipo_tolerancia_gral,tipo_temperatura_inicial;
int next_segmento,next_tiempo,next_tol,next_prog;
int Lim_Segmento;
//////////////////////////////////

////////////////////////////////////////////////////////////////////////
//ACCION AL SALIR DEL BOX DE SELECCION DE PROGRAMA//////////////////////
////////////////////////////////////////////////////////////////////////

void A_Programa(void){

  for(Lim_Segmento=0;Programa[programa_ingresado].Segmento[Lim_Segmento].tipo_segmento!=End;Lim_Segmento++);
segmento_ingresado=0;
BoxAnterior =  PROGRAMA;
}

////////////////////////////////////////////////////////////////////////
//ACCION AL INGRESAR AL BOX DE SELECCION DE SEGMENTO//////////////////////
////////////////////////////////////////////////////////////////////////

void A_Ingreso_Segmento(void){
extern int ValorTmp;
TSegmentos * dir;
char end[]="End ";  
  if (BoxAnterior==NOPROGRAMA){
  //grabar
  BufferSegmento.tipo_segmento= tipo_segmento;
  BufferSegmento.condicion_emer = (byte) condicion_emer;
  BufferSegmento.tipo_tolerancia = (byte)tipo_tolerancia;
  BufferSegmento.temperatura_f = temperatura_f;
  BufferSegmento.tiempo = tiempo; 
  BufferSegmento.tolerancia = tolerancia;

  datos_grabar = (word *)&BufferSegmento;
  dir = &Programa[programa_ingresado].Segmento[0];
  dir+= segmento_ingresado-1;
  direccion_grabar = (word)dir;
  *(word*)indice_datos=1023;
  cant_datos_grabar = TAMANIO_SEGMENTO;

  save_array =TRUE;
  
  //Actualizar
    if (segmento_ingresado==MAX_SEGMENTOS){    
    PasarASCII(end,0);     //DisplaySup
    Lim_Segmento=segmento_ingresado=ValorTmp=MAX_SEGMENTOS-1;
    }
  
  }else BoxAnterior = NOPROGRAMA;
  
}

////////////////////////////////////////////////////////////////////////
//ACCION AL SALIR DEL BOX DE SELECCION DE SEGMENTO//////////////////////
////////////////////////////////////////////////////////////////////////


void A_Segmento(void){
  if (!segmento_ingresado){ //Si es igual a 0, cargo la info de esos boxes
  tipo_temperatura_inicial = general.tipo_temperatura_inicial; 
  temperatura_inicial = general.temperatura_inicial;
  tipo_tolerancia_gral = general.tipo_tolerancia;
  tolerancia_gral = general.tolerancia;
  condicion_emer_gral = general.condicion_emer; 
  }else{
      if (general.tipo_tolerancia==no){
      next_tiempo=0; //ir a tolerancia(next box)
        if(general.condicion_emer==no){
        next_prog=next_tol = 0;  // ir a Condicon de emergencia(next box)
        }else {
          next_prog=next_tol = 1;//ir a segmento     
        }
      }
      else if (general.condicion_emer==no){
        next_prog=0;	 //ir a Condicon de emergencia(next box)
        next_tiempo=1; //ir a Condicon de emergencia(next box)
      }else{
        next_tiempo=2; //ir a segmento
        next_prog=1;	 //ir a segmento
      }
  }

tipo_segmento = segmento.tipo_segmento;
temperatura_f = segmento.temperatura_f;
tiempo = segmento.tiempo;
tolerancia =  segmento.tolerancia;
tipo_tolerancia = segmento.tipo_tolerancia;
condicion_emer = segmento.condicion_emer;


next_segmento = !segmento_ingresado; // Proximo box 
  
segmento_ingresado++;
Lim_Segmento++;
}


////////////////////////////////////////////////////////////////////////
//ACCION AL SALIR DEL BOX DE CONDICION DE EMERGENCIA GENERAL////////////
////////////////////////////////////////////////////////////////////////

void A_Condicion_Emergencia_General(void){


   if (tipo_tolerancia_gral==no){
      next_tiempo=0; //ir a tolerancia(next box)
        if(condicion_emer_gral==no){
        next_prog=next_tol = 0;  // ir a Condicon de emergencia(next box)
        }else {
          next_prog=next_tol = 1;//ir a segmento     
        }
      }
      else if (condicion_emer_gral==no){
        next_prog=0;	 //ir a Condicon de emergencia(next box)
        next_tiempo=1; //ir a Condicon de emergencia(next box)
      }else{
        next_tiempo=2; //ir a segmento
        next_prog=1;	 //ir a segmento
      }
       

//grabar
BufferGeneral.tipo_temperatura_inicial = (byte)tipo_temperatura_inicial; 
BufferGeneral.temperatura_inicial = temperatura_inicial;
BufferGeneral.tipo_tolerancia = (byte)tipo_tolerancia_gral;
BufferGeneral.tolerancia = tolerancia_gral;
BufferGeneral.condicion_emer = condicion_emer_gral; 
datos_grabar = (word *)&BufferGeneral;
direccion_grabar = (word)&Programa[programa_ingresado].Gral;
indice_datos[0]=255;
cant_datos_grabar = TAMANIO_GENERAL;

save_array =TRUE;
}

/////////////////////Actualiza el Set Point Actual (Se llama a cada segundo)//////////////////////////////

void ActualizarSetPointPrograma(byte canal){
bool CambioSeg=FALSE;
long int TmpSet;

  if(SegVal[canal].tolerancia){
    switch(SegVal[canal].tipo_tolerancia){
      case bAnd:
      case Lo: if((ValFinal[canal]+SegVal[canal].tolerancia)<SetPointPrograma[canal])
             return; 
      case Hi: if((ValFinal[canal]-SegVal[canal].tolerancia)>SetPointPrograma[canal])
             return;
    }
  }
SegundosSegmento[canal]++;

  switch(SegVal[canal].tipo_segmento){
    case rMPt: TmpSet = (SegVal[canal].temperatura_f- TemperaturaAnterior[canal])*SegundosSegmento[canal];
               TmpSet /= (SegVal[canal].tiempo*60);
               SetPointPrograma[canal] = (int)TmpSet+TemperaturaAnterior[canal];
    
    case MSt:		
    
    case SteP:if(SegundosSegmento[canal] >= SegVal[canal].tiempo*60) CambioSeg=TRUE;
   						break;
    
    case rMPV:

             TmpSet =	 SegVal[canal].velocidad * SegundosSegmento[canal] /60;
             SetPointPrograma[canal] = (int)TmpSet;
                if (pendiente_negativa)
                  SetPointPrograma[canal]*=-1;
             SetPointPrograma[canal] += TemperaturaAnterior[canal];     
                  if ((pendiente_negativa &&
                  SetPointPrograma[canal]<=SegVal[canal].temperatura_f) ||
                  (!pendiente_negativa && 
                  SetPointPrograma[canal]>=SegVal[canal].temperatura_f)
                  ){
                  SetPointPrograma[canal]=SegVal[canal].temperatura_f;  
                  CambioSeg=TRUE;
                  }

    					break;
 //   case JMP: 
     	
    
    case End:
    return;		
  }

  if(CambioSeg){
    
  CambioSeg=FALSE;
  
  TemperaturaAnterior[canal] = (int)SetPointPrograma[canal];
  
  runPrograma(canal,ProgramaActual[canal],++SegmentoActual[canal]);    
  }
}

////////////////// Carga los valores iniciales de un programa/////////////
//Aclaracion: nunca entra con tipo_segmento= JMP
void runPrograma(byte canal,byte programa, byte Segmento){
extern word TiempoProgramaCh[CANTIDAD_SAL_CONTROL];
TSegmentos * p,* segval;
byte ProgramaAux;
byte i=MAX_PROGRAMAS;

if (!Segmento)
    ProgramReturn[canal][programa].Programa=0;

segval=&SegVal[canal];
    
  do{
  p=& Programa[programa].Segmento[Segmento];  
     
     switch(p->tipo_segmento){
       case SteP:
          SetPointPrograma[canal] = p->temperatura_f;
          break;
       case rMPV:
       case MSt:
       case rMPt: 
          if (!Segmento){
            if (Programa[programa].Gral.tipo_temperatura_inicial == AMb)
            SetPointPrograma[canal]=TemperaturaAnterior[canal] = ValFinal[canal];
            else //SEt
            SetPointPrograma[canal]=TemperaturaAnterior[canal] = Programa[programa].Gral.temperatura_inicial;
          }
        break;
       
       case JMP: 
        i--;
        ProgramReturn[canal][p->sub_programa].Programa = programa+1;
        ProgramReturn[canal][p->sub_programa].Segmento = Segmento;
        ProgramReturn[canal][p->sub_programa].Ciclos = (byte)p->ciclos;
       
        programa=(byte)p->sub_programa;
        Segmento=0;        
          if (!i)return;//ERROR ****AGREGAR MAS COSAS*****
			  break;
       
       case End:
          if(!ProgramReturn[canal][programa].Programa){
          segval->tipo_segmento = End;  
          return;
          }
          if(ProgramReturn[canal][programa].Ciclos>1){
          ProgramReturn[canal][programa].Ciclos--;
          Segmento=0;
          }else{
          Segmento=ProgramReturn[canal][programa].Segmento+1; 
          ProgramaAux=programa;
          programa=ProgramReturn[canal][programa].Programa-1;
          ProgramReturn[canal][ProgramaAux].Programa=0;     
          }
       break;
     }
  }while(p->tipo_segmento==JMP || p->tipo_segmento==End);
   
if(p->tipo_segmento==rMPV)
  pendiente_negativa = p->temperatura_f < TemperaturaAnterior[canal];  
         
segval->tipo_segmento = p->tipo_segmento;
segval->temperatura_f = p->temperatura_f;
segval->tiempo  			= p->tiempo;

if(Programa[programa].Gral.tipo_tolerancia!=no)
{
  segval->tipo_tolerancia=Programa[programa].Gral.tipo_tolerancia;
  segval->tolerancia= Programa[programa].Gral.tolerancia;
}else{
  segval->tipo_tolerancia = p->tipo_tolerancia; 
  segval->tolerancia = p->tolerancia;
}
 
SegundosSegmento[canal]=0;
ProgramaActual[canal]=programa;
SegmentoActual[canal]=Segmento;

}

//////////Funcion al caerse la Energia.IMPLEMENTADO COMO MACRO
/*
void GuardarPrograma(void){
(void)WriteArray(FLASH_APAGADO_START,0, (7+3*MAX_PROGRAMAS)*CANTIDAD_SAL_CONTROL, (word*)ProgramaActual);
}
*/
///////////////////////////Funcion al caerse la Energia/////
//Aclaracion: nunca entra con tipo_segmento= JMP
void ReestablecerPrograma(byte canal){
TSegmentos *p;
byte CondicionTmp;
register unsigned i;

for(i=0;i<(7+3*MAX_PROGRAMAS)*CANTIDAD_SAL_CONTROL;i+=2)
  *(word*)(ProgramaActual+i) = *(word*)(FLASH_APAGADO_START+i);

if (ProgramReturn[canal][ProgramaActual[canal]].Programa
  && ((CondicionTmp=Programa[ProgramReturn[canal][ProgramaActual[canal]].Programa-1].Segmento[ProgramReturn[canal][ProgramaActual[canal]].Segmento].condicion_emer)!=no)) {
  if (CondicionTmp!=cc){
    SegmentoActual[canal] = ProgramReturn[canal][ProgramaActual[canal]].Segmento;
    ProgramaActual[canal] = ProgramReturn[canal][ProgramaActual[canal]].Programa-1;
  }
}
else if ((CondicionTmp=(byte)Programa[ProgramaActual[canal]].Gral.condicion_emer)!=no);
else CondicionTmp = Programa[ProgramaActual[canal]].Segmento[SegmentoActual[canal]].condicion_emer;

switch(CondicionTmp){
  case rS: runPrograma(canal,ProgramaActual[canal], SegmentoActual[canal]);
  				 break;
  case rP: runPrograma(canal,ProgramaActual[canal], 0);
  				 break;
  case EndP:
    EscribirParametro(R_Programa+canal,-1);          
    break;
  case cc:
  p=& Programa[ProgramaActual[canal]].Segmento[SegmentoActual[canal]];  
  if(p->tipo_segmento==rMPV)
    pendiente_negativa = p->temperatura_f < TemperaturaAnterior[canal];

  SegVal[canal].tipo_segmento = p->tipo_segmento;
  SegVal[canal].temperatura_f = p->temperatura_f;
  SegVal[canal].tiempo  			= p->tiempo;

  
  if(Programa[ProgramaActual[canal]].Gral.tipo_tolerancia!=no){
    SegVal[canal].tipo_tolerancia=Programa[ProgramaActual[canal]].Gral.tipo_tolerancia;
    SegVal[canal].tolerancia= Programa[ProgramaActual[canal]].Gral.tolerancia;
  }else{
    SegVal[canal].tipo_tolerancia = p->tipo_tolerancia; 
    SegVal[canal].tolerancia = p->tolerancia;
  }

}

(void) EraseSectorInternal(FLASH_APAGADO_START);
}
#endif