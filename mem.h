void set_ebp(int value) ;

int get_ebp() ;

void mem_init();

void init_var_globales(int nb)  ; 

/**
 * Return 0 if success, return -1 on error
 */
int mem_set(int addr, int valeur);

int mem_get(int addr); 
