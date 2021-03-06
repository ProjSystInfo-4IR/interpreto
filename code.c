#include "code.h"
#include "y.tab.h"
#include "mem.h"
#include "stack.h"
#include "dumb-logger/logger.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define CAPACITE 1000  // maximum de 1000 lignes du code ASM
#define CAPACITE_STACK_ARGUMENTS 20 // 20 arguments maximum par fonction
#define CAPACITE_STACK_ADRESS_RETOUR 100 
#define MARQUEUR_VIDE -1

/* structure d'une instruction ASM */
struct code {
  int opcode;
  int arg1;
  int arg2;
  int arg3;
  char* arg_str;
};

/* le fichier ASM est représenté par un tableau d'instructions */ 
struct code EXEC_CODE[CAPACITE];


int lineNum; // nombre de lignes du fichier ASM 
stack args_stack, retaddr_stack; // piles d'arguments et piles d'adresse de retour 

/* initialisation des deux piles et de la mémoire */ 
void code_init() {     
  stack_init(&args_stack, CAPACITE_STACK_ARGUMENTS);
  stack_init(&retaddr_stack, CAPACITE_STACK_ADRESS_RETOUR);     
  mem_init();     
  lineNum = 0 ; 
}

/* codeX_ajouter(....) : ajouter au tableau d'instructions une instruction en fonction du nombre d'arguments (X) */ 

int code0_ajouter(int opcode) {
  EXEC_CODE[lineNum].opcode = opcode;
  EXEC_CODE[lineNum].arg1 = MARQUEUR_VIDE;
  EXEC_CODE[lineNum].arg2 = MARQUEUR_VIDE;
  EXEC_CODE[lineNum].arg3 = MARQUEUR_VIDE;
  lineNum++;
  return 0;
}

int code1_ajouter(int opcode, int arg1) {
  EXEC_CODE[lineNum].opcode = opcode;
  EXEC_CODE[lineNum].arg1 = arg1;
  EXEC_CODE[lineNum].arg2 = MARQUEUR_VIDE;
  EXEC_CODE[lineNum].arg3 = MARQUEUR_VIDE;
  lineNum++;
  return 0;
}

int code1_ajouter_str(int opcode, char* arg) {
  EXEC_CODE[lineNum].opcode = opcode;
  EXEC_CODE[lineNum].arg1 = MARQUEUR_VIDE;
  EXEC_CODE[lineNum].arg2 = MARQUEUR_VIDE;
  EXEC_CODE[lineNum].arg3 = MARQUEUR_VIDE;
  EXEC_CODE[lineNum].arg_str = arg;
  lineNum++;
  return 0;
}

int code2_ajouter(int opcode, int arg1, int arg2) {
  EXEC_CODE[lineNum].opcode = opcode;
  EXEC_CODE[lineNum].arg1 = arg1;
  EXEC_CODE[lineNum].arg2 = arg2;
  EXEC_CODE[lineNum].arg3 = MARQUEUR_VIDE;
  lineNum++;
  return 0;
}

int code3_ajouter(int opcode, int arg1, int arg2, int arg3) {
  EXEC_CODE[lineNum].opcode = opcode;
  EXEC_CODE[lineNum].arg1 = arg1;
  EXEC_CODE[lineNum].arg2 = arg2;
  EXEC_CODE[lineNum].arg3 = arg3;
  lineNum++;
  return 0;
}



/* enlever les guillements d'un string 
 * et bidouille pour remplacer les characteres \n par le vrai \n (ASCII : 34 92 => 10)
 */ 
char* process_string(char* str) {
  int i = 0, j;
  // nombre de charactere nouvelle ligne
  int nl_num = 0;
  char* res = malloc(sizeof(strlen(str)) - 1);
  j = 0;
  for (i = 1; i < strlen(str) - 1; i++) {
    res[j] = str[i];
    if (i < strlen(str) - 2) {
      if (str[i] == '\\' && str[i+1] == 'n') {
        res[i-1] = '\n';
        i++;
        nl_num++;
      }
    }
    j++;
  }
  res[strlen(str) - 2 - nl_num] = 0; 
  return res;
} 


int code_run() { int cur_line = 1; int tmp;
  while(cur_line <= lineNum) {
    struct code c = EXEC_CODE[cur_line - 1];
    cur_line++;
    switch (c.opcode) {
    case tADD :
      mem_set(c.arg1, mem_get(c.arg2) + mem_get(c.arg3));
      break;
    case tSOU :
      mem_set(c.arg1, mem_get(c.arg2) - mem_get(c.arg3));
      break;
    case tMUL :
      mem_set(c.arg1, mem_get(c.arg2) * mem_get(c.arg3));
      break;
    case tDIV :
      mem_set(c.arg1, mem_get(c.arg2) / mem_get(c.arg3));
      break;
    case tCOP :
      mem_set(c.arg1, mem_get(c.arg2));
      break;
    case tAFC :
      mem_set(c.arg1, c.arg2);
      break;
    case tJMP :
      cur_line = c.arg1;
      break;
    case tJMF :
      if (mem_get(c.arg1) == 0) {
	cur_line = c.arg2;
      }
      break;
    case tPRI : 
      if (c.arg1 != MARQUEUR_VIDE) {
	if (logger_get_level() == LOGGER_VERBOSE) {
	  logger_info("We have %d at address %d\n", mem_get(c.arg1), c.arg1);
	} else {
	  printf("%d", mem_get(c.arg1));
	}
      } else {
	printf("%s", process_string(c.arg_str));
      }
      break;
    case tCALL : 
      logger_info("Appel addresse %d de  %d. Il faut sauter au dessus de %d variables \n", c.arg1, cur_line-1, c.arg2);
      init_var_globales(c.arg2) ; 
      if (stack_push(&retaddr_stack, get_ebp()) == -1) { // push actuel bas de pile
	return -1;
      }
      if (stack_push(&retaddr_stack, cur_line) == -1) { // push return address
	return -1;
      }
      set_ebp(get_ebp() + c.arg2 + 1) ; // mise à jour du bas de la pile 
      logger_info("Bas de pile changé à : %d \n", get_ebp());
      cur_line = c.arg1;
      break;
    case tRET : 
      if ((tmp = stack_pop(&retaddr_stack)) == -1) {
	return -1;
      }
      cur_line = tmp; 
      if ((tmp = stack_pop(&retaddr_stack)) == -1) {
	return -1;
      }
      set_ebp(tmp) ; 
      logger_info("Bas de pile remis à l'origne (à : %d)\n", get_ebp());
      logger_info("Return to address %d \n", cur_line);				
      break;
    case tLEAVE : 
      logger_info("LEAVE détecté ; fin du programme\n");
      return 0;
    case tPUSH : 
      stack_push(&args_stack, mem_get(c.arg1));
      break;
    case tPOP : 
      mem_set(c.arg1, stack_pop(&args_stack));
      break;
    default: 
      logger_error("%d : Unknown opcode %d\n", cur_line, c.opcode);
      return -1;
    }
  }
  return -1;
}

void code_print() { 
  int i;
  logger_info("Tableau du code executable : \n");
  for (i = 0; i < lineNum; i++) {
    logger_info("L%2d : %3d %3d %3d %3d\n", i, 
		EXEC_CODE[i].opcode, 
		EXEC_CODE[i].arg1, 
		EXEC_CODE[i].arg2,
		EXEC_CODE[i].arg3);
  }
}


void code_destroy() {
  stack_destroy(&args_stack);
  stack_destroy(&retaddr_stack);
}
