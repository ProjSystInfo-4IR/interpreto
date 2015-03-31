%{
#include <stdio.h>

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
Instruction : tADD NOMBRE NOMBRE NOMBRE { printf("%d %d %d\n", $2, $3, $4); }

%%

int yyerror(char *s) {
  printf("%s\n",s);
}

int main(void) {

  yyin = fopen("tests/test1.asm", "r");
  return yyparse();
}
