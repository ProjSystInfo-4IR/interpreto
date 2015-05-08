#include "mem.h"
#include "dumb-logger/logger.h"

#include <stdio.h>
#include <limits.h> // pour INT_MIN

#define CAPACITE_TAS 1000

/* la mémoire est représentée par un tableau C */  
int TAS[CAPACITE_TAS];


void mem_init() { int i;
  for (i = 0; i < CAPACITE_TAS; i++) {
    TAS[i] = INT_MIN;
  }
}

int mem_set(int addr, int valeur)
{
  if (addr < 0 || CAPACITE_TAS <= addr) {
    logger_error("Segmentation fault : unable to access to address %d\n", addr);
    return -1;
  }
  TAS[addr] = valeur;
  return 0;
}

int mem_get(int addr) {
  if (addr < 0 || CAPACITE_TAS <= addr) {
    logger_error("Segmentation fault : unable to access to address %d\n", addr);
    return -1;
  }
  return TAS[addr];
}
