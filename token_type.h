#ifndef _TOKEN_TYPE_H
#define _TOKEN_TYPE_H

typedef enum TokenType {
	TK_AND,
	TK_CLASS,
	TK_ELSE,
	TK_FALES,
	TK_FOR,
	TK_FUN,
	TK_IF,
	TK_NIL,
	TK_OR,
	TK_PRINT,
	TK_RETURN,
	TK_SUPER,
	TK_THIS,
	TK_TRUE,
	TK_VAR,
	TK_WHILE,

	//=============

	TK_LEFT_PAREN,        // (
	TK_RIGHT_PAREN,       // )

	TK_LEFT_BRACE,        // {
	TK_RIGHT_BRACE,       // }

	TK_COMMA,             // ,
	TK_SEMICOLON,         // ;
	TK_DOT,               // .
	TK_BANG,              // !

	TK_PLUS,              // +
	TK_MINUS,             // -
	TK_STAR,              // *
	TK_SLASH,             // /
	TK_EQUAL,             // =

	TK_LESS,              // <
	TK_GREATER,           // >
	TK_LESS_EQUAL,        // < =
	TK_GREATER_EQUAL,     // > =
	TK_EQUAL_EQUAL,       // ==
	TK_BANG_EQUAL,        // !=

	TK_NUMBER,
	TK_IDENTIFIER,
	TK_STRING,

	TK_EOF,
	TK_NULL,
}TokenType;

#endif // _TOKEN_TYPE_H
