///////////////////////////////////////////////////////////////////////////
// matriz de decodificacion para display de 7 segmentos
/*
         _        0x20
		|_|  0x01;0x02;0x04
		|_|. 0x08;0x10;0x40; 0x080
*/

///////////////////////////////////////////////////////////////////////////
#include "matriz.h"

#pragma CONST_SEG DEFAULT  

const unsigned char Car_Ini[]=	{
							
0x02,					// -	ok
0x80,					// .	ok
0x0E,					// /
0x7D,					// 0	ok
0x44,					// 1	ok
0x3E,					// 2	ok
0x76,					// 3	ok
0x47,					// 4	ok
0x73,					// 5	ok
0x7B,					// 6	ok
0x64,					// 7	ok
0x7F,					// 8	ok
0x77,					// 9 	ok
0x46,					// : (lo uso como -1) ok
0x6A,					// ;
0x3E,					// <
0x76,					// =
0x47,					// >
0x73,					// ?
0x7B,					// @
0x6F,					// A	ok
0x7F,					// B
0x39,					// C	0k
0x7B,					// D
0x3B,					// E	ok
0x2B,					// F	ok
0x79,					// G	ok
0x4F,					// H	ok
0x09,					// I	ok
0x5C,					// J	ok
0x4F,					// K	ok
0x19,					// L	ok
0x6D,			    // M
0x7F,					// N
0x7D,					// O	ok
0x2F,					// P	ok
0x67,					// Q
0x7F,					// R
0x73,					// S	ok
0x7B,					// T	
0x5D,					// U	ok
0x5D,					// V	ok (=U)
0x77,					// W
0x7B,					// X
0x57,					// Y
0x7F,					// Z
0x77,					// [
0x7B,					// \
0x64,					// ]	// 5d
0x7F,					// ^
0x1,					//  Agregado
0x10,					// _	ok	
0x7B,					// `
0x7E,					// a	ok
0x5B,					// b	ok
0x1A,					// c	ok
0x5E,					// d	ok
0x3F,					// e	ok
0x7F,					// f	
0x77,					// g
0x4B,					// h	ok
0x08,					// i	ok
0x7F,					// j
0xF ,					// k
0x09,					// l	ok
0x6D,			    // m	ok
0x4A,					// n	ok
0x5A,					// o	ok										
0x7B,					// p
0x67,					// q
0x0A,					// r	ok
0x77,					// s
0x1B,					// t	ok
0x58,					// u	ok
0x7F,					// v
0x77,					// w
0x7B,					// x
0x57,					// y
0x7F,					// z
					
};	

