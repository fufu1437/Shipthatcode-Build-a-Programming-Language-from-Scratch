#ifndef _LSTRING_H
#define _LSTRING_H

#include <stdio.h>

typedef struct LString {
	char* val;
	size_t use;
	size_t cap;
}LString;

LString* lstring_new();

void lstring_free(LString* ls);

int lstring_addChar(LString* ls, char c);

int lstring_addCString(LString* ls, const char* cs);
int lstring_addCString_safe(LString* ls, const char* cs, size_t len);

int lstring_set(LString* ls, char c, size_t index);

#endif // _LSTRING_H
