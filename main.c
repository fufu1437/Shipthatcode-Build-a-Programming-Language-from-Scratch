#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "token.h"
#include "token_type.h"
#include "lstring.h"

static int is_keyword(const char* w) {
	static const char* KW[] = { "and","class","else","false","for","fun","if","nil", \
		"or","print","return","super","this","true","var","while", NULL };
	for(int i = 0; KW[i]; i++) if(strcmp(KW[i], w) == 0) return 1;
	return 0;
}

int main(void) {
	char* src = NULL; size_t cap = 0; int c;
	size_t len = 0;
	while((c = getchar()) != EOF) {
		if(len + 1 >= cap) { cap = cap ? cap * 2 : 64; src = realloc(src, cap); }
		src[len++] = (char)c;
	}
	if(src) src[len] = 0;

	int line = 1;
	Token* tks = tokenize(src);
	token_print(tks);
	printf("EOF  null\n");
	free(src);
	return 0;
}

#include "lstring.c"
#include "token.c"
