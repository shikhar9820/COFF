/* Standard Headers */
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>

/* Local Headers */
#include "coff.h"

/* ------------------------------------------------------------------------- */

#define command_flush(x) char_flush(x, PATH_MAX)
#define filename_flush(x) command_flush(x)

/* ------------------------------------------------------------------------- */

char command[PATH_MAX];
static int c_cpp(const char[], const struct arguments);

/* ------------------------------------------------------------------------- */

int compile_test(const struct arguments coff_arguments){

  /* --Python-- */
  if( strcmp("python", coff_arguments.lang) == 0 ){
    print_err("Please specify \"python3\" or \"python2\"");
    return 1;
  }

  if( strcmp("python2", coff_arguments.lang) == 0 ||
      strcmp("python3", coff_arguments.lang) == 0 )
    return 0;

  /* --Javascript */
  if( strcmp("javascript", coff_arguments.lang) == 0 ||
      strcmp("js", coff_arguments.lang) == 0 )

    return 0;
  /* --C-- */
  if( strcmp("c", coff_arguments.lang) == 0 ){
    return c_cpp("gcc", coff_arguments);
  }

  /* --C++-- */
  if( strcmp("c++", coff_arguments.lang) == 0 ){
    return c_cpp("g++", coff_arguments);
  }
  
  /* --C++11-- */
  if( strcmp("c++11", coff_arguments.lang) == 0 ){
    return c_cpp("g++ -std=c++11", coff_arguments);
  }

  /* --C++17-- */
  if( strcmp("c++17", coff_arguments.lang) == 0 ){
    return c_cpp("g++ -std=c++17", coff_arguments);
  }


  return 0;
}
/* ------------------------------------------------------------------------- */

static int c_cpp(const char compiler[], const struct arguments coff_arguments){
  int status;
  char path[PATH_MAX];

  chdir(coff_config.test_directory);
  status = expand_file_path(path, coff_arguments.test_file);
  if(status)
    return status;

  command_flush(command);
  strcpy(command, compiler);
  strcat(command, " -o coff_testing ");
  strcat(command, path);

  if(coff_config.opt & 0x10){
    strcat(command, " ");
    strcat(command, coff_arguments.flag);
  }

  printf("\n-----------------------------------------------------------------\
---------------");
  printf("\nCompiling: %s", command);
  status = system(command);
  if(status)
    return status;

  printf("\nCompiled Successfully !!");
  printf("\n-----------------------------------------------------------------\
---------------\n");

  return 0;
}

/* ------------------------------------------------------------------------- */
