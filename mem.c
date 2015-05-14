#include "mem.h"
#include <stdio.h>
#include <limits.h> // pour INT_MIN

#define CAPACITE_TAS 1000

int TAS[CAPACITE_TAS];
int ebp ; // bas du tas (relatif)
int nb_var_globales  ; 
int var_globales_init ; 

void set_ebp(int value) {
  ebp = value ;  
}

int get_ebp() {
  return ebp ;  
}

void init_var_globales(int nb) {
  if (var_globales_init == 0){
    nb_var_globales = nb ; 
    var_globales_init = 1 ; 
  }
}

void mem_init() { int i;
  for (i = 0; i < CAPACITE_TAS; i++) {
    TAS[i] = INT_MIN;
  }
  set_ebp(0) ; 
  var_globales_init = 0 ; 
}

int mem_set(int addr, int valeur)
{
  if (addr >= nb_var_globales) { addr = addr + ebp ; }
  if (addr < 0 || CAPACITE_TAS <= addr) {
    printf("Segmentation fault : unable to access to address %d\n", addr);
    return -1;
  }
  TAS[addr] = valeur;
  return 0;
}

int mem_get(int addr) {
  if (addr >= nb_var_globales) { addr = addr + ebp ; }
  if (addr < 0 || CAPACITE_TAS <= addr) {
    printf("Segmentation fault : unable to access to address %d\n", addr);
    return -1;
  }
  return TAS[addr];
}
