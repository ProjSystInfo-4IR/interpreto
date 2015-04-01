%{
#include <stdio.h>
#include "mem.h"

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
Instruction : tADD NOMBRE NOMBRE NOMBRE { mem_set($2, mem_get($3) + mem_get($4)); }
			| tSOU NOMBRE NOMBRE NOMBRE { mem_set($2, mem_get($3) - mem_get($4)); }
			| tMUL NOMBRE NOMBRE NOMBRE { mem_set($2, mem_get($3) * mem_get($4)); }
			| tDIV NOMBRE NOMBRE NOMBRE { mem_set($2, mem_get($3) / mem_get($4)); }
			| tCOP NOMBRE NOMBRE        { mem_set($2, mem_get($3)); }
			| tAFC NOMBRE NOMBRE        { mem_set($2, $3); }
			| tPRI NOMBRE               { printf("A l'adresse %d j'ai %d\n", $2, mem_get($2));}

%%

int yyerror(char *s) {
  	printf("%s\n",s);
}

int main(void) {

	mem_init();

  	yyin = fopen("tests/test1.asm", "r");
  	return yyparse();
}
