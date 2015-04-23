#include "stack.h"
#include "dumb-logger/logger.h"
#include <stdio.h>
#include <limits.h> // pour INT_MIN

#define CAPACITE_STACK 5

int STACK[CAPACITE_STACK];
/**
 *   Stack pointer
 */
int sp;

void stack_init() { int i;
	for (i = 0; i < CAPACITE_STACK; i++) {
		STACK[i] = INT_MIN;
	}
	sp = 0;
}

int stack_push(int value) {
	if (sp == CAPACITE_STACK - 1) {
		printf("Stackoverflow error : no more space to push to stack \n");
		return -1;
	}
	STACK[sp] = value;
	sp++;
	return 0;
}

int stack_pop() {
	if (sp == 0) {
		printf("Stack empty error : no value to pop from stack\n");
		return -1;
	}
	sp--;
	return STACK[sp];
}

void stack_print() { int i;
	logger_info("Tableau du pile : \n");
	logger_info("Adresse - Valeur\n");
	for (i = 0; i < sp; i++) {
		logger_info("  %2d      %4d\n", i, STACK[i]);
	}
}