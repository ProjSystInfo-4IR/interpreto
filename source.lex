/*** Definition section ***/
 
%{
/* C code to be copied verbatim */
#include <stdio.h>
#include "y.tab.h"
%}

SPACE  	[\t ]+
EOL  	[\n]+
DIGITS 	[0-9]+
FUNCNAME [a-zA-Z][a-zA-Z0-9_]*
STRING \".*\"
%option yylineno
%x COMMENT
%%

"#" 			{BEGIN COMMENT;}  // line-comment begins with #
<COMMENT>\n 	{BEGIN INITIAL;}
<COMMENT>.		{}                // consume all characters 

 /*** Rules section ***/
{SPACE} ;     // élimine blancs et tabs   /*** Astuce qui ne marche pas : ajouter EOL en fin de fichier <<EOF>> { static int once = 0; return once++ ? 0 : '\n' ;} **/
{EOL}         return tEOL;         //return tSPACE ;
ADD 		  return tADD; 
MUL           return tMUL;  
SOU           return tSOU;  
DIV      	  return tDIV; 
COP        	  return tCOP; 
AFC     	  return tAFC; 
JMP           return tJMP; 
JMF       	  return tJMF; 
INF        	  return tINF; 
SUP           return tSUP;  
EQU           return tEQU;  
PRI           return tPRI;
CALL          return tCALL;
RET           return tRET;
LEAVE         return tLEAVE; 
PUSH          return tPUSH;
POP           return tPOP;   
{DIGITS} 	{ yylval.nombre=atoi(yytext); 
			  return NOMBRE;
			}
{FUNCNAME} 	{ yylval.chaine = strdup(yytext); 
			  return FNAME; 
			}
{STRING}    { yylval.string = strdup(yytext); 
			  return STRING; 
			}
 
%%

/*** C Code section 
 
int main(void)
{
    // Call the lexer, then quit. 
    yylex();
    return 0;
}

 ***/
