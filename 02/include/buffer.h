/* THIS FILE IS PART OF THE ASSIGNMENT AND MUST NOT BE CHANGED! */

#ifndef _BUFFER_H
#define _BUFFER_H

int yylen;    /* the length of the current token */
char* yytext; /* the current token */

void buffer_init();       /* initialize buffer */
void buffer_add(char c);  /* add a character to current buffer */
void buffer_reset();      /* reset the buffer to an empty string */
void buffer_destroy();    /* deallocate all allocated memory */

#endif
