#ifndef _TOKENS_H
#define _TOKENS_H

#include "symboltable.h"

/* an enumeration of all tokens */
typedef enum {
    KEY_ARRAY, KEY_BEGIN, KEY_CHAR, KEY_CONST, KEY_DO, KEY_ELSE, KEY_ELSIF,
	KEY_END, KEY_FOR, KEY_IF, KEY_INTEGER, KEY_MODULE, KEY_OF, KEY_PROCEDURE,
	KEY_REAL, KEY_REPEAT, KEY_RETURN, KEY_THEN, KEY_TO, KEY_TYPE, KEY_UNTIL,
	KEY_VAR, KEY_WHILE, ASSIGN, OR, AND, EQ, NE, LE, GE, LEQ, GEQ, PLUS,
	MINUS, ASTERISK, SLASH, DIV, MOD, NOT, SEMICOLON, PERIOD, COLON, COMMA,
	LPAREN, RPAREN, LBRACK, RBRACK, RANGE, IDENT, INTEGER, REAL, CHAR, STRING
} token_t;

/* an element of the token list */
typedef struct token_list_element {
    token_t type;                        /* token type */
    union {
        char* string_constant;           /* value of STRING/IDENT */
        char char_constant;              /* value of CHAR */
        int integer_constant;            /* value of INTEGER */
        double real_constant;            /* value of REAL */
    } value;
    struct token_list_element* next;     /* pointer to next element */
} token_list_element;

void append(token_t);       /* add a token to the list */
void output_token_list();   /* output the token list to yyout */

int iskeyword();            /* returns -1 iff current token is not a keyword */

#endif
