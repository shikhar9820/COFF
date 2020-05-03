#include <stdio.h>

#include "coff.h"

int main(int argc, char *argv[]){
  if(argc == 1){
    print_err("Not enough enough argument.\n"
                "Try : coff -h");
  }
}
