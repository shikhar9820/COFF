/* Standard Headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Local Headers */
#include "coff.h"

/* ------------------------------------------------------------------------- */

int read_question(const char file[]){
  FILE *infile;

  char path[PATH_MAX];

  struct question q;
  struct constraints cons;
  struct example examp;

  unsigned int i;

  /* change current working directory */
  chdir(coff_config.quest_directory);
  if((i = expand_file_path(path, file)) != 0)
    return i;

  infile = fopen(path, "rb");
  if(infile == NULL){
    print_err("Could not open file.");
  }

  if(fread(&q, sizeof(struct question), 1, infile) == 0)
    print_err("Could not read content.");

  else{
    printf("\nQuestion: %s\n", q.name);
    printf("\nDescription:\n%s\n", q.question);
  }

  if(fread(&cons, sizeof(struct constraints), 1, infile) == 0)
    print_err("Could not read content.");

  for(i=0; i<q.no_of_examples; i++){
    if(fread(&examp, sizeof(struct example), 1, infile) == 0){
      print_err("Could not read content.");
      continue;
    }
    printf("\n\nExample no %u", i+1);
    printf("\n Example input:  %s", examp.input);
    printf("\n Example output: %s", examp.output);

  }

  printf("\n--------------------------------------------------------------\n");

  fclose(infile);
  chdir(coff_config.cwd);
  return 0;
  
  
}
