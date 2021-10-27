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

void yyerror(const char *msg) {
    printf("%s\n", msg);
    free(yytext);
    exit(EXIT_FAILURE);
}

void reset_yy() {
    for (int i = 0; i < yylen; ++i) yytext[i] = '\0'; // could use MAX_SIZE for safety instead yylen
    yylen = 0;
}

bool is_keyword() {  // yytext has at least len 1
    int low = 0;
    int mid = AMOUNT_KEY / 2;
    int high = AMOUNT_KEY;
    int compare;
    int *ptr_high_low;

    while (true) {
        if (mid == low || mid == high) break;

        compare = strcmp(yytext, KEYWORDS[mid]);
        if (compare != 0) {
            ptr_high_low = (compare < 0) ? &high : &low;
            *ptr_high_low = mid;  // save to the direct address of either high or low
            mid = (low + high) / 2;
        } else return true;
    }
    return false;
}

void generic_flush(const char *end, FILE *outfile) {
    if (outfile) fprintf(outfile, "%s%s", yytext, end);
    else printf("%s%s", yytext, end);
    reset_yy();
}

void generic_read_write(FILE *infile, FILE *outfile) {
    char c;
    bool is_identifier = false;
    size_t buffer_length = 0;

    while ((c = (infile ? getc(infile) : getchar())) != EOF) {
        if (yylen == MAX_SIZE) { // Buffer full (GUARD)
            ++buffer_length;
            generic_flush("", outfile);
        }

        if (is_identifier) {  // "usual" state
            if (isalnum(c)) yytext[yylen++] = c; // continue id
            else {
                is_identifier = false;
                if (buffer_length) {  // KEYWORDS have to be at start, so no need to check
                    buffer_length = 0;
                    generic_flush("\n", outfile);
                } else {
                    if (!is_keyword()) generic_flush("\n", outfile);
                    else reset_yy();  // only reset without printing
                }
            }
        } else {
            if (isalpha(c)) {  // start of identifier
                is_identifier = true;
                yytext[yylen++] = c;
            }
        }
    }
}

int main(int argc, char **argv) {
    yytext = (char *) calloc(MAX_SIZE, sizeof(char));

    if (argc > 3) yyerror("error: wrong number of parameters");
    const MODE mode = (MODE) argc;

    FILE *infile;
    FILE *outfile;

    if (mode != STD_READ_STD_WRITE) {  // only no file in std_read
        infile = fopen(argv[1], "r");
        if (infile == NULL) yyerror("error: cannot open file for reading");
    } else infile = NULL;
    if (mode == FILE_READ_FILE_WRITE) {  // only file to write in file_write
        outfile = fopen(argv[2], "a");
        if (outfile == NULL) {
            if (infile) fclose(infile); // close before EXIT_FAILURE
            yyerror("error: cannot open file for writing");
        }
    } else outfile = NULL;

    generic_read_write(infile, outfile);

    if (mode == FILE_READ_FILE_WRITE) fclose(outfile);
    if (mode != STD_READ_STD_WRITE) fclose(infile);

    free(yytext);

    return EXIT_SUCCESS;
}
