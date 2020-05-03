#include <stdio.h>

#include "coff.h"

int print_err(const char a[]){
  return fprintf(stderr, "\nError: %s\n", a);
}
