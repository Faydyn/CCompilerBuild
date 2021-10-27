#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "include/buffer.h"
#include "include/diagnosis.h"
#include "include/tokens.h"
#include "include/scanner.h"


int main(int argc, char* argv[]) {
	int i;
	int keyword_index;

	/* initialize global variables */
	yyin = stdin;
	yyout = stdout;
	buffer_init();

	/* process command line parameters for input and output */
	if (argc > 3) {
		yyerror("wrong number of parameters");
	}
	if (argc > 1) {
		yyin = fopen(argv[1], "r");
		if (yyin == NULL) {
			yyerror("cannot open file for reading");
		}
	}
	if (argc > 2) {
		yyout = fopen(argv[2], "w");
		if (yyout == NULL) {
			yyerror("cannot open file for writing");
		}
	}

    /* ADD YOUR CODE HERE */

	buffer_destroy();
	fclose(yyin);
	fclose(yyout);

	return 0;
}
