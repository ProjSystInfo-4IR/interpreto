#include "code.h"
#include "y.tab.h"
#include "mem.h"
#include "dumb-logger/logger.h"
#include <stdio.h>

#define CAPACITE 1000
#define MARQUEUR_VIDE -1

struct code {
	int opcode;
	int arg1;
	int arg2;
	int arg3;
};

struct code EXEC_CODE[CAPACITE];
int lineNum;

void code_init() {
	mem_init();
	lineNum = 0;
}

int code1_ajouter(int opcode, int arg1) {
	EXEC_CODE[lineNum].opcode = opcode;
	EXEC_CODE[lineNum].arg1 = arg1;
	EXEC_CODE[lineNum].arg2 = MARQUEUR_VIDE;
	EXEC_CODE[lineNum].arg3 = MARQUEUR_VIDE;
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

void code_run() { int cur_line = 0;
	while(cur_line <= lineNum) {
		struct code c = EXEC_CODE[cur_line];
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
				cur_line = c.arg1 - 1;
				break;
			case tJMF :
				if (mem_get(c.arg1) == 0) {
					cur_line = c.arg2 - 1;
				}
				break;
			case tPRI : 
				printf("%d\n", mem_get(c.arg1));
				logger_info("Printed value at address %d\n", c.arg1);
				break;
		}
		cur_line++;
	}
}

void code_print() { int i;
	for (i = 0; i < lineNum; i++) {
		logger_info("L%2d : %3d %3d %3d %3d\n", i, 
			EXEC_CODE[i].opcode, 
			EXEC_CODE[i].arg1, 
			EXEC_CODE[i].arg2,
			EXEC_CODE[i].arg3);
	}
}
