#ifndef _TOKEN_H
#define _TOKEN_H

#include "token_type.h"
#include "lstring.h"

typedef struct Token {
	TokenType type;
	double number;
	size_t line;
	LString* v;
	size_t cow;
}Token;

Token* tokenize(char* code);
char* token_str(TokenType type);
void token_print(Token* tks);

#endif // _TOKEN_H
