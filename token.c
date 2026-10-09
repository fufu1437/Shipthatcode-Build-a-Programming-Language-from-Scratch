#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "token.h"

static int toke_is_keyword(const char* w, TokenType* t) {
	static const char* KW[] = { "and","class","else","false","for","fun","if","nil", \
		"or","print","return","super","this","true","var","while", NULL };
	for(int i = 0; KW[i]; i++) if(strcmp(KW[i], w) == 0) { *t = i; return 1; }
	return 0;
}

Token* tokenize(char* code) {
	Token* tks = malloc(sizeof(Token) * 1024);
	memset(tks, 0, sizeof(Token) * 1024);

	size_t index = 0;

	size_t line = 0;
	size_t cow = 0;

#define cc (*code)
#define peek (*(code + 1))

	LString* buf = lstring_new();;

	while(cc) {
		if(isspace(cc)) {
			if(cc == '\n') {
				line++; cow = 0;
			}
		}
		else if(cc == '(') {
			tks[index].line = line;	tks[index].cow = cow;
			tks[index++].type = TK_LEFT_PAREN;
		}
		else if(cc == ')') {
			tks[index].line = line;	tks[index].cow = cow;
			tks[index++].type = TK_RIGHT_PAREN;
		}
		else if(cc == '{') {
			tks[index].line = line;	tks[index].cow = cow;
			tks[index++].type = TK_LEFT_BRACE;
		}
		else if(cc == '}') {
			tks[index].line = line;	tks[index].cow = cow;
			tks[index++].type = TK_RIGHT_BRACE;
		}
		else if(cc == ',') {
			tks[index].line = line;	tks[index].cow = cow;
			tks[index++].type = TK_COMMA;
		}
		else if(cc == ';') {
			tks[index].line = line;	tks[index].cow = cow;
			tks[index++].type = TK_SEMICOLON;
		}
		else if(cc == '.') {
			tks[index].line = line;	tks[index].cow = cow;
			tks[index++].type = TK_DOT;
		}
		else if(cc == '+') {
			tks[index].line = line;	tks[index].cow = cow;
			tks[index++].type = TK_PLUS;
		}
		else if(cc == '-') {
			tks[index].line = line;	tks[index].cow = cow;
			tks[index++].type = TK_MINUS;
		}
		else if(cc == '*') {
			tks[index].line = line;	tks[index].cow = cow;
			tks[index++].type = TK_STAR;
		}
		else if(cc == '/') {
			tks[index].line = line;	tks[index].cow = cow;
			tks[index++].type = TK_SLASH;
		}
		else if(cc == '=') {
			tks[index].line = line;	tks[index].cow = cow;
			if((*(code + 1)) == '=') {
				tks[index++].type = TK_EQUAL_EQUAL;
				code++; cow++;
			}
			else {
				tks[index++].type = TK_EQUAL;
			}
		}
		else if(cc == '<') {
			tks[index].line = line;	tks[index].cow = cow;
			if((*(code + 1)) == '=') {
				tks[index++].type = TK_LESS_EQUAL;
				code++; cow++;
			}
			else {
				tks[index++].type = TK_LESS;
			}
		}
		else if(cc == '>') {
			tks[index].line = line;	tks[index].cow = cow;
			if((*(code + 1)) == '=') {
				tks[index++].type = TK_GREATER_EQUAL;
				code++; cow++;
			}
			else {
				tks[index++].type = TK_GREATER;
			}
		}
		else if(cc == '!') {
			tks[index].line = line;	tks[index].cow = cow;
			if((*(code + 1)) == '=') {
				tks[index++].type = TK_BANG_EQUAL;
				code++; cow++;
			}
			else {
				tks[index++].type = TK_BANG;
			}
		}
		else if(cc == '"') {
			code++; cow++;
			LString* o_string = lstring_new();
			lstring_addChar(o_string, '"');
			while(cc != '"' && cc != '\n') {
				if(cc == '\\') {
					lstring_addChar(o_string, cc);
					code++; cow++;
					if(cc == 'n') {
						lstring_addChar(buf, '\n');
					}
					else if(cc == 'b') {
						lstring_addChar(buf, '\b');
					}
					else if(cc == '\"') {
						lstring_addChar(buf, '\"');
					}
					else if(cc == '\\') {
						lstring_addChar(buf, '\\');
					}
					else if(cc == 't') {
						lstring_addChar(buf, '\t');
					}
					lstring_addChar(o_string, cc);
				}
				else {
					lstring_addChar(buf, cc);
					lstring_addChar(o_string, cc);
				}
				code++; cow++;
			}
			if(cc != '"') {
				fprintf(stderr, "[line %d] Error: Unterminated string.", line);
			}
			lstring_addChar(o_string, '"');
			tks[index].cow = cow;
			tks[index].line = line;
			tks[index].v = buf;
			tks[index].o_v = o_string;
			tks[index++].type = TK_STRING;
			buf = lstring_new();
		}
		else if(isalpha(cc) || cc == '_') {
			while(isalnum(cc) || cc == '_') {
				lstring_addChar(buf, cc);
				code++; cow++;
			}
			code--; cow--;
			tks[index].cow = cow;
			tks[index].line = line;
			tks[index].v = buf;

			TokenType t;
			if(toke_is_keyword(buf->val, &t) == 1) {
				tks[index++].type = t;
			}
			else {
				tks[index++].type = TK_IDENTIFIER;
			}

			buf = lstring_new();
		}
		else if(isalnum(cc)) {
			while((cc >= '0' && cc <= '9') || cc == '.') {
				lstring_addChar(buf, cc);
				code++; cow++;
			}
			code--; cow--;
			double number = strtod(buf->val, NULL);
			tks[index].v = buf;
			tks[index].cow = cow;
			tks[index].line = line;
			tks[index].number = number;
			tks[index++].type = TK_NUMBER;
			buf = lstring_new();
		}
		else {
			fprintf(stderr, "[line %d] Error: Unexpected character: %c\n", line, cc);
		}
		code++; cow++;
	}
	tks[index++].type = TK_EOF;
	do {
		void* t = realloc(tks, sizeof(Token) * index);
		if(t != NULL) tks = t;
	} while(0);
	return tks;
}

char* token_str(TokenType type) {
	switch(type) {
	case TK_BANG:          return "BANG !";
	case TK_BANG_EQUAL:    return "BANG_EQUAL !=";
	case TK_COMMA:         return "COMMA ,";
	case TK_DOT:           return "DOT .";
	case TK_EQUAL:         return "EQUAL =";
	case TK_EQUAL_EQUAL:   return "EQUAL_EQUAL ==";
	case TK_GREATER:       return "GREATER >";
	case TK_GREATER_EQUAL: return "GREATER_EQUAL >=";
	case TK_LEFT_BRACE:    return "LEFT_BRACE {";
	case TK_LEFT_PAREN:    return "LEFT_PAREN (";
	case TK_LESS:          return "LESS <";
	case TK_LESS_EQUAL:    return "LESS_EQUAL <=";
	case TK_MINUS:         return "MINUS -";
	case TK_PLUS:          return "PLUS +";
	case TK_RIGHT_BRACE:   return "RIGHT_BRACE }";
	case TK_RIGHT_PAREN:   return "RIGHT_PAREN )";
	case TK_SEMICOLON:     return "SEMICOLON ;";
	case TK_SLASH:         return "SLASH /";
	case TK_STAR:          return "STAR *";

	case TK_NUMBER:        return "NUMBER";
	case TK_IDENTIFIER:    return "IDENTIFIER";

	case TK_AND:           return "AND";
	case TK_CLASS:         return "CLASS";
	case TK_ELSE:          return "ELSE";
	case TK_FALES:         return "FALES";
	case TK_FOR:           return "FOR";
	case TK_FUN:           return "FUN";
	case TK_IF:            return "IF";
	case TK_NIL:           return "NIL";
	case TK_OR:            return "OR";
	case TK_PRINT:         return "PRINT";
	case TK_RETURN:        return "RETURN";
	case TK_SUPER:         return "SUPER";
	case TK_THIS:          return "THIS";
	case TK_TRUE:          return "TRUE";
	case TK_VAR:           return "VAR";
	case TK_WHILE:         return "WHILE";
	case TK_STRING:        return "STRING";

	case TK_EOF:           return "EOF";

	default:               return "NULL";
	}
}

void token_print(Token* tks) {
	if(tks == NULL) return;
	size_t index = 0;
	while(tks[index].type != TK_EOF) {
		Token tk = tks[index];
		if(tk.type == TK_NUMBER) {
			printf("NUMBER %s %.1f\n", tk.v->val, tk.number);
		}
		else if(tk.type == TK_IDENTIFIER || (tk.type >= TK_AND && tk.type <= TK_WHILE)) {
			printf("%s %s null\n", token_str(tk.type), tk.v->val);
		}
		else if(tk.type == TK_STRING) {
			printf("STRING %s %s\n", tk.o_v->val, tk.v->val);
		}
		else {
			printf("%s null\n", token_str(tk.type));
		}
		index++;
	}
}
