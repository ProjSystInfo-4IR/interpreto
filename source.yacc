%{
#include <stdio.h>
#include <unistd.h> // getopt
#include "code.h"
#include "dumb-logger/logger.h"
extern FILE * yyin;
%}

%token tEOL
%token tADD tMUL tSOU tDIV
%token tCOP tAFC
%token tJMP tJMF
%token tINF tSUP tEQU 
%token tPRI
%error-verbose
%token <nombre> NOMBRE
%union {int nombre;}

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
			;
%%

int yyerror(char *s) {
  	logger_error("%s\n",s);
}

int main(int arg, char** argv ) { int i; FILE* inputFile;

	if ((inputFile = fopen(argv[1], "r")) == NULL) {
		logger_error("Cannot open input file %s\n", argv[optind]);
		return -1;
	}
	yyin = inputFile;
	logger_set_level(LOGGER_VERBOSE);

	code_init();
  	
  	i = yyparse();
  	
  	code_print();

  	code_run();

  	return i;
}
