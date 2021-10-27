/* THIS FILE IS PART OF THE ASSIGNMENT AND MUST NOT BE CHANGED! */

#ifndef __SCANNER_H
#define __SCANNER_H

#include <stdio.h>

FILE* yyin;   /* input file */
FILE* yyout;  /* output file */
int yylineno; /* line number */
char ch;      /* the last read character */

char next_char();  /* get a character from yyin */

void scanID();     /* scan an IDENT or keywords */
int scanNUMBER();  /* scan an INTEGER (return 0) or REAL (return 1) */
void scanSTRING(); /* scan a STRING */
void scanCHAR();   /* scan a CHAR */

#endif
