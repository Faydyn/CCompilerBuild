/* THIS FILE IS PART OF THE ASSIGNMENT AND MUST NOT BE CHANGED! */

#include <stdlib.h>
#include <string.h>
#include "../include/buffer.h"
#include "../include/diagnosis.h"

int capacity;

void buffer_init() {
    yylen = 0;
    capacity = 1;
    yytext = (char*) calloc(capacity, sizeof(char));
    if (yytext == NULL) {
        yyerror("could not allocate memory");
    }
}

void buffer_add(char c) {
    /* resize token if necessary */
    if (yylen+1 >= capacity) {
        capacity *= 2;
        yytext = (char*) realloc(yytext, capacity);
        if (yytext == NULL) {
            yyerror("could not allocate memory");
        }
    }

    /* store current character */
    yytext[yylen++] = c;
    yytext[yylen] = '\0';
}

void buffer_reset() {
    /* reset token buffer */
    memset(yytext, 0, capacity);
    yylen = 0;
}

void buffer_destroy() {
    free(yytext);
}
