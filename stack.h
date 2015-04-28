

typedef struct stack_struct {
	int* mem;
	int capacity;
	/**
	 *   Stack pointer
	 */
	int sp;
} stack;


void stack_init(stack* s, int capacity);

int stack_push(stack* s, int value);

int stack_pop(stack* s);

void stack_print(stack* s);

void stack_destroy(stack* s);