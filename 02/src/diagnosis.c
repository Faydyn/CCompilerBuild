/* THIS FILE IS PART OF THE ASSIGNMENT AND MUST NOT BE CHANGED! */

#include <stdio.h>
#include <stdlib.h>
#include "../include/diagnosis.h"
#include "../include/scanner.h"

void yyerror(char const* msg) {
    fprintf(stderr, "error: %s\n", msg);
    if (ch != EOF) {
        fprintf(stderr, "last read character: '%c'\n", ch);
    }
    exit(1);
}
