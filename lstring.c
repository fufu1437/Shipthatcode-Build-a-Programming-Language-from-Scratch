#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lstring.h"

#define LSTRING_DEFAULT_CAP 10
int LSTRING_DEFAULT_RE = 1.5;

int lstring_adjust(LString* ls) {
	if(ls == NULL) return 1;

	size_t ns = ls->cap * LSTRING_DEFAULT_RE;
	char* nc = realloc(ls->val, ns);
	if(nc == NULL) return 1;

	ls->val = nc;
	ls->cap = ns;

	return 0;
}

LString* lstring_new() {
	LString* ls = malloc(sizeof(LString));
	if(ls == NULL) { return NULL; }
	ls->val = malloc(sizeof(char) * LSTRING_DEFAULT_CAP);
	if(ls->val == NULL) {
		free(ls);
		return NULL;
	}
	ls->use = 0;
	ls->cap = LSTRING_DEFAULT_CAP;
	return ls;
}

void lstring_free(LString* ls) {
	if(ls == NULL) return;
	free(ls);
	if(ls->val == NULL) { return; }
	free(ls->val);
	ls->cap = 0;
	ls->use = 0;
}

int lstring_addChar(LString* ls, char c) {
	if(ls == NULL) return 1;
	if(ls->val == NULL) return 2;
	if(ls->use >= ls->cap) {
		lstring_adjust(ls);
	}
	ls->val[ls->use++] = c;
	ls->val[ls->use] = 0;
	return 0;
}

int lstring_addCString(LString* ls, const char* cs) {
	if(ls == NULL || cs == NULL) return 1;
	size_t len = strlen(cs);
	return lstring_addCString_safe(ls, cs, len);
}

int lstring_addCString_safe(LString* ls, const char* cs, size_t len) {
	if(ls == NULL || cs == NULL) return 1;
	for(size_t i = 0; i < len;i++) {
		lstring_addChar(ls, cs[i]);
	}
	return 0;
}

int lstring_set(LString* ls, char c, size_t index) {
	if(ls == NULL) return 1;
	if(index >= ls->use) return 2;
	ls->val[index] = c;
	return 0;
}
