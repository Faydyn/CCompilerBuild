#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 16
#define AMOUNT_KEY 23
#define bool int
#define false 0
#define true 1

#define KEYWORDS_ENABLED 0

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
    for (int i = 0; i < yylen; ++i) yytext[i] = '\0'; // TODO: IS THIS CORRECT??
    yylen = 0;
}

void print_reset_yytext(const char *eol) {

    printf("%s%s", yytext, eol);
    reset_yytext();
}

bool is_keyword() {  // id has at least len 1
    // TODO: Binary search
    for (int i = 0; i < AMOUNT_KEY; ++i) {
        const char *key = KEYWORDS[i];
        // printf("Key: %s\n", key);
        // printf("%d\n", yylen);
        // printf("%lu\n", strlen(key) - 1);

        if (yylen == strlen(key - KEYWORDS_ENABLED)) {
            for (int j = 0; j <= yylen; ++j) {  // \0 sign can be ignored here, since has to be identical
                if (j == yylen) return true;
                else if (yytext[j] != key[j]) break;
            }
        }
    }
    return false;
}

void read_from_std() {

    char c;
    bool is_identifier = false;
    size_t buffer_length = 0;

    while ((c = getchar()) != EOF) {
        if (!is_identifier) {
            if (isalpha(c)) {  // start of id (GUARD)
                is_identifier = true;
                yytext[yylen++] = c;
            }
        } else {
            if (yylen == MAX_SIZE) { // Buffer full (GUARD)
                ++buffer_length;
                print_reset_yytext("");  // dont eol here
            } else {
                if (isalnum(c)) yytext[yylen++] = c; // continue id
                else {
                    is_identifier = false;
                    if (buffer_length) {  // KEYWORDS have to be at start, so no need to check
                        buffer_length = 0;
                        print_reset_yytext("\n");
                    } else {
                        if (!is_keyword()) print_reset_yytext("\n");  // dont print keywords (see #define on top)
                        else reset_yytext();  // only reset without printing
                    }
                }
            }
        }

    }
}

void read_from_file(char *inpath) {
    FILE *infile = fopen(inpath, "r");
    if (infile == NULL) yyerror("error: cannot open file for reading");

    char c;
    bool is_identifier = false;
    size_t buffer_length = 0;

    while ((c = getc(infile)) != EOF) {
        if (!is_identifier) {
            if (isalpha(c)) {  // start of id (GUARD)
                is_identifier = true;
                yytext[yylen++] = c;
            }
        } else {
            if (yylen == MAX_SIZE) { // Buffer full (GUARD)
                ++buffer_length;
                print_reset_yytext("");  // dont eol here
            } else {
                if (isalnum(c)) yytext[yylen++] = c; // continue id
                else {
                    is_identifier = false;
                    if (buffer_length) {  // KEYWORDS have to be at start, so no need to check
                        buffer_length = 0;
                        print_reset_yytext("\n");
                    } else {
                        if (!is_keyword()) print_reset_yytext("\n");  // dont print keywords (see #define on top)
                        else reset_yytext();  // only reset without printing
                    }
                }
            }
        }

    }
    fclose(infile);
}

void read_write_to_file(char *inpath, char *outpath) {
    FILE *infile = fopen(inpath, "r");
    if (infile == NULL) yyerror("error: cannot open file for reading");

    FILE *outfile = fopen(outpath, "a");
    if (outfile == NULL) yyerror("error: cannot open file for writing");

    char c;
    bool is_identifier = false;
    size_t buffer_length = 0;

    while ((c = getc(infile)) != EOF) {
        if (!is_identifier) {
            if (isalpha(c)) {  // start of id (GUARD)
                is_identifier = true;
                yytext[yylen++] = c;
            }
        } else {
            if (yylen == MAX_SIZE) { // Buffer full (GUARD)
                ++buffer_length;
                fprintf(outfile, "%s", yytext);
                reset_yytext();
            } else {
                if (isalnum(c)) yytext[yylen++] = c; // continue id
                else {
                    is_identifier = false;
                    if (buffer_length) {  // KEYWORDS have to be at start, so no need to check
                        buffer_length = 0;
                        fprintf(outfile, "%s\n", yytext);
                        reset_yytext();
                        print_reset_yytext("\n");
                    } else {
                        if (!is_keyword()) {
                            fprintf(outfile, "%s\n", yytext);
                            reset_yytext();
                        } else reset_yytext();  // only reset without printing
                    }
                }
            }
        }

    }

    fclose(infile);
    fclose(outfile);
}


int main(int argc, char **argv) {
    const MODE mode = (MODE) argc;
    yytext = (char *) calloc(MAX_SIZE, sizeof(char));

// use isdigit(), isalpha(), isalnum()
    switch (mode) {
        case STD_READ_STD_WRITE:

            read_from_std();
            break;

        case FILE_READ_STD_WRITE:
            read_from_file(argv[1]);

            break;

        case FILE_READ_FILE_WRITE:
            read_write_to_file(argv[1], argv[2]);
            break;

        default:
            yyerror("error: wrong number of parameters");
    }

    free(yytext);
    return 0;
}

