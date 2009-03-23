#ifndef	OBJECT_H
#define	OBJECT_H

#include <stdarg.h>
#include <stddef.h>
#include <stdtypes.h>
#include <stdio.h>
#include "Object.r"


//extern const void * Object;		/* new(&Object); */
extern const struct Class Object;

void * new (const void * class, ...);
void * newAlloced (void * _self,const void * classOf, ...);
void delete (void * self);
void deleteAlloced (void * _self);
void deleteAndNil (void ** _self);
                                 
const void * classOf (const void * self);
uchar instanceOf(const void * _self,struct Class * class);
size_t sizeOf (const void * self);

void * ctor (void * self, va_list * app);
void * dtor (void * self);
int differ (const void * _self, const void * b);
int puto (const void * _self, struct OutputStream * os);

//extern const void * Class;	/* new(&Class, "name", super, size
//										sel, meth, ... 0); */
extern const struct Class Class;

const void * super (const void * self);	/* class' superclass */

#endif
