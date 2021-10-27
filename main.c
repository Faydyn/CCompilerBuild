#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 16
#define AMOUNT_KEY 23
#define bool int
#define false 0
#define true 1

// yy-Variables and -Functions are required (see "Vorgaben")
char *yytext;
int yylen;

const char *KEYWORDS[AMOUNT_KEY] = {"ARRAY",
                                    "BEGIN",
                                    "CHAR",
                                    "CONST",
                                    "DO",
                                    "ELSE",
                                    "ELSIF",
                                    "END",
                                    "FOR",
                                    "IF",
                                    "INTEGER",
                                    "MODULE",
                                    "OF",
                                    "PROCEDURE",
                                    "REAL",
                                    "REPEAT",
                                    "RETURN",
                                    "THEN",
                                    "TO",
                                    "TYPE",
                                    "UNTIL",
                                    "VAR",
                                    "WHILE"};

typedef enum mode {
    STD_READ_STD_WRITE = 1,
    FILE_READ_STD_WRITE,
    FILE_READ_FILE_WRITE,
} MODE;

void yyerror(char *msg) {
    printf("%s\n", msg);
    free(yytext);
    exit(EXIT_FAILURE);
}

void reset_yytext() {
    for(int i = 0; i < yylen; ++i) yytext[i] = '\0'; // TODO: IS THIS CORRECT??
    yylen = 0;
}
void print_reset_yytext(){
    printf("%s\n",yytext);
    reset_yytext();
}

bool is_keyword() {  // id has at least len 1
    // TODO: Binary search
    for (int i = 0; i < AMOUNT_KEY; ++i) {
        const char *key = KEYWORDS[i];
        // printf("Key: %s\n", key);
        // printf("%d\n", yylen);
        // printf("%lu\n", strlen(key) - 1);

        if (yylen == strlen(key) - 1) {
            for (int j = 0; j <= yylen; ++j) {  // \0 sign can be ignored here, since has to be identical
                if (j == yylen) return true;
                else if (yytext[j] != key[j]) break;
            }
        }
    }
    return false;
}

void read_from_file(char *path, MODE mode) {
    FILE *infile = fopen(path, "r");
    if (infile == NULL) yyerror("error: cannot open file for reading");

    char c;
    bool is_identifier = false;
    size_t buffer_length = 0;

    while ((c = getc(infile)) != EOF) {
        if (!is_identifier) {
            if (isalpha(c)) {  // start of id
                is_identifier = true;
                yytext[yylen++] = c;
            }
        } else {
            if (yylen == MAX_SIZE) { // Buffer full
                ++buffer_length;
                print_reset_yytext();
            } else {
                if (isalnum(c)) yytext[yylen++] = c; // continue id
                else {
                    is_identifier = false;
                    if (buffer_length) {  // KEYWORDS have to be at start, so no need to check
                        buffer_length = 0;
                        print_reset_yytext();
                    } else {
                        if(!is_keyword()) print_reset_yytext();
                        else reset_yytext();
                    }
                }
            }
        }

    }
    fclose(infile);
}

void write_to_file(char *path) {
    FILE *outfile = fopen(path, "w");
    if (outfile == NULL) yyerror("error: cannot open file for writing");

    fclose(outfile);
}



int main(int argc, char **argv) {
    const MODE mode = (MODE) argc;
    yytext = (char *) calloc(MAX_SIZE, sizeof(char));

// use isdigit(), isalpha(), isalnum()
    switch (mode) {
        case STD_READ_STD_WRITE:

            printf("%s", argv[0]);
            break;

        case FILE_READ_STD_WRITE:
            read_from_file(argv[1], mode);

            break;

        case FILE_READ_FILE_WRITE:
            read_from_file(argv[1], mode);

            printf("%s\n", argv[0]);
            printf("%s\n", argv[1]);
            printf("%s", argv[2]);
            break;

        default:
            yyerror("error: wrong number of parameters");
    }

    free(yytext);
    return 0;
}
/*
 *
 MODULE KW
 HelloWorld
 TYPE KW
 myInt
 INTEGER  X KW
 CONST KW
 pi
 VAR KW
 x
 REAL KW
 BEGIN KW
 f
 pi
 END
 HelloWorld
 */

