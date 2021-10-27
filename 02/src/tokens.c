#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/tokens.h"

extern char* yytext;
extern FILE* yyout;

const char* token_names[] = {
    "KEY_ARRAY", "KEY_BEGIN", "KEY_CHAR", "KEY_CONST", "KEY_DO", "KEY_ELSE",
	"KEY_ELSIF", "KEY_END", "KEY_FOR", "KEY_IF", "KEY_INTEGER", "KEY_MODULE",
	"KEY_OF", "KEY_PROCEDURE", "KEY_REAL", "KEY_REPEAT", "KEY_RETURN",
	"KEY_THEN", "KEY_TO", "KEY_TYPE", "KEY_UNTIL", "KEY_VAR", "KEY_WHILE",
	"ASSIGN", "OR", "AND", "EQ", "NE", "LE", "GE", "LEQ", "GEQ", "PLUS",
	"MINUS", "ASTERISK", "SLASH", "DIV", "MOD", "NOT", "SEMICOLON", "PERIOD",
	"COLON", "COMMA", "LPAREN", "RPAREN", "LBRACK", "RBRACK", "RANGE", "IDENT",
	"INTEGER", "REAL", "CHAR", "STRING"
};

token_list_element* token_list = NULL;
token_list_element* last = NULL;

/* ADD YOUR CODE HERE */
