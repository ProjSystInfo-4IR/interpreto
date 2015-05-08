#include "stack.h"
#include "dumb-logger/logger.h"

#include <stdio.h>
#include <limits.h> // pour INT_MIN
#include <stdlib.h>

/* extrait du fichier stack.h ; représentation d'une pile  

typedef struct stack_struct {
	int* mem;
	int capacity;
	int sp; // stack pointer 
} stack;

*/ 

void stack_init(stack* s, int capacity) { int i;
	s->capacity = capacity;
	s->mem = malloc(sizeof(int)*capacity);
	for (i = 0; i < s->capacity; i++) {
		s->mem[i] = INT_MIN;
	}
	s->sp = 0;
}

int stack_push(stack* s, int value) {
	if (s->sp == s->capacity - 1) {
		printf("Stackoverflow error : no more space to push to stack \n");
		return -1;
	}
	s->mem[s->sp] = value;
	s->sp++;
	return 0;
}

int stack_pop(stack* s) {
	if (s->sp == 0) {
		printf("Stack empty error : no value to pop from stack\n");
		return -1;
	}
	s->sp--;
	return s->mem[s->sp];
}

void stack_print(stack* s) { int i;
	logger_info("Representation de la pile : \n");
	logger_info("Adresse - Valeur\n");
	for (i = 0; i < s->sp; i++) {
		logger_info("  %2d      %4d\n", i, s->mem[i]);
	}
}

void stack_destroy(stack* s) {
	free(s->mem);
	s->capacity = 0;
	s->sp = 0;
}
