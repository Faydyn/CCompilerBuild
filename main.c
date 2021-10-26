#include <stdio.h>
#include <stdlib.h>

#define AMOUNT_KEY 23

// yy-Variables and -Functions are required (see "Vorgaben")
char *yytext;
int yylen;

char *KEYWORDS[AMOUNT_KEY];
enum mode;

void yyerror(char *msg);

void read_from_file(char *path);
void write_to_file(char *path);


char *KEYWORDS[AMOUNT_KEY] = {"ARRAY",
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
    exit(EXIT_FAILURE);
}

void read_from_file(char *path) {
    FILE *infile;
    infile = fopen(path, "r");
    if (infile == NULL) yyerror("error: cannot open file for reading");

    char c;
    while ((c = getc(infile)) != EOF) {
        printf("%c", c);
    }
    fclose(infile);
}

void write_to_file(char *path) {
    FILE *outfile;
    outfile = fopen(path, "w");
    if (outfile == NULL) yyerror("error: cannot open file for writing");

    fclose(outfile);
}

int main(int argc, char **argv) {

    MODE mode;
    FILE *outfile;

    mode = (MODE) argc;

// use isdigit(), isalpha(), isalnum()
    switch (mode) {
        case STD_READ_STD_WRITE:

            printf("%s", argv[0]);
            break;

        case FILE_READ_STD_WRITE:
            read_from_file(argv[1]);

            break;

        case FILE_READ_FILE_WRITE:


            printf("%s\n", argv[0]);
            printf("%s\n", argv[1]);
            printf("%s", argv[2]);
            break;

        default:
            yyerror("error: wrong number of parameters");
    }


    return 0;
}


