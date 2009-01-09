#ifndef _FRIEND_CONTROL_H
#define _FRIEND_CONTROL_H

#include "Control.h"

#pragma CONST_SEG PARAMETERS_PAGE
extern volatile const int InternalSP[CANTIDAD_SAL_CONTROL];
extern volatile const int LimInfSP[CANTIDAD_SAL_CONTROL];
extern volatile const int LimSupSP[CANTIDAD_SAL_CONTROL];
extern volatile const TPeriod Period[CANTIDAD_SAL_CONTROL];
extern volatile const int Reset[CANTIDAD_SAL_CONTROL];
extern volatile const int Histeresis[CANTIDAD_SAL_CONTROL];
extern volatile const T_TipoControl eTipoControl[CANTIDAD_SAL_CONTROL];

#pragma CONST_SEG DEFAULT

#endif