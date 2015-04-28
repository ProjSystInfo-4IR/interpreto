
void code_init();

int code0_ajouter(int opcode);

int code1_ajouter(int opcode, int arg1);

int code2_ajouter(int opcode, int arg1, int arg2);

int code3_ajouter(int opcode, int arg1, int arg2, int arg3);

int code_run();

void code_print();

void code_destroy();
