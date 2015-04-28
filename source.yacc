%{
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // getopt
#include <errno.h>  // error code

#include "code.h"
#include "dumb-logger/logger.h"

extern int yylineno;
extern FILE * yyin;
char* inputFileName;
%}
%token tEOL
%token tADD tMUL tSOU tDIV
%token tCOP tAFC
%token tJMP tJMF
%token tINF tSUP tEQU 
%token tPRI
%token tCALL tRET tLEAVE
%token tPUSH tPOP
%error-verbose
%token <nombre> NOMBRE
%union {int nombre;}
%token <chaine> FNAME
%union {char* chaine;} 
%token <string> STRING
%union {char* string;} 
%start Input
%%

Input: Instructions ;
 
Instructions: Instruction tEOL Instructions
			| ;
Instruction:  tADD NOMBRE NOMBRE NOMBRE 	{ code3_ajouter(tADD, $2, $3, $4); }
			| tSOU NOMBRE NOMBRE NOMBRE 	{ code3_ajouter(tSOU, $2, $3, $4); }
			| tMUL NOMBRE NOMBRE NOMBRE 	{ code3_ajouter(tMUL, $2, $3, $4); }
			| tDIV NOMBRE NOMBRE NOMBRE 	{ code3_ajouter(tDIV, $2, $3, $4); }
			| tCOP NOMBRE NOMBRE        	{ code2_ajouter(tCOP, $2, $3); }
			| tAFC NOMBRE NOMBRE        	{ code2_ajouter(tAFC, $2, $3); }
			| tJMF NOMBRE NOMBRE        	{ code2_ajouter(tJMF, $2, $3); }		
			| tJMP NOMBRE               	{ code1_ajouter(tJMP, $2); }
			| tPRI NOMBRE               	{ code1_ajouter(tPRI, $2); }
			| tPRI STRING                   { code1_ajouter_str(tPRI, $2); }
			| tCALL NOMBRE                  { code1_ajouter(tCALL, $2); }
			| tPUSH NOMBRE                  { code1_ajouter(tPUSH, $2); }
			| tPOP NOMBRE                   { code1_ajouter(tPOP, $2); }
			| tRET                          { code0_ajouter(tRET); }
			| tLEAVE                        { code0_ajouter(tLEAVE); }
			;
%%

int yyerror(char *s) {
  	logger_error("%s:%d : %s\n", inputFileName, yylineno, s);
}

int main(int argc, char** argv ) { int i, opt; FILE* inputFile;
	inputFileName = malloc(20*sizeof(char));

    while ((opt = getopt(argc, argv, "v")) != -1) {
	    switch (opt) {
			case 'v' : 
			  // enables verbose mode
			  logger_set_level(LOGGER_VERBOSE);
			  break;
	  	}
    }
	
	if (optind == argc) {
    	logger_error("No input file specified\n");
    	return EXIT_FAILURE;
  	}

	if ((inputFile = fopen(argv[optind], "r")) == NULL) {
		logger_error("Cannot open input file %s\n", argv[optind]);
		return -1;
	}

	yyin = inputFile;
	inputFileName = argv[1];

	code_init();
  	
  	i = yyparse();
  	if (i == 0) {
  		code_print();
  		code_run();
  	}

  	code_destroy();

  	return i;
}
