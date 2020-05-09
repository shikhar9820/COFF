/* Standard Headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Local Headers */
#include "coff.h"

void read_string(char a[], unsigned int i){
  unsigned int j;
  fgets(a, i, stdin);
  for(j=0; j<=i; j++){
  i
  }
}

int main()
{
  FILE *outfile;
  char file[PATH_MAX_len];
  char temp[coff_quest_size_len];
  struct question q;
  struct test_case test;
  struct constraints cons;
  struct example examples;
  unsigned int i, j;

  read_config();

  char_flush(file, PATH_MAX_len);
  strcpy(file, coff_config.quest_directory);
  strcat(file, "/newQuestion.quest");
  printf("\nThe Question will be written in: %s", file);

  outfile = fopen(file, "wb");
  if (outfile == NULL) {
    print_err("Could not open file.");
    exit(1);
  }

  printf("\nEnter the Question-Name (Max %u characters): ",
         coff_quest_name_size);
  fflush(stdin);
  char_flush(q.name, coff_quest_name_size_len);
  fscanf(stdin, "%[^\n]s", q.name);
  q.name[coff_quest_name_size_len] = '\0';

  printf("\nEnter the Question-Statement (Hit Enter when done writing) (Max \
%u characters)\nStart: ",
         coff_quest_size);
  fflush(stdin);
  char_flush(q.question, coff_quest_size_len);
  fscanf(stdin, "%[^\n]s", q.question);
  q.question[coff_quest_size_len] = '\0';
 
  /* Input no of examples */ 
  j=1;
  while(j == 1){
    printf("\nEnter the no of examples: ");
    fflush(stdin);
    char_flush(temp, coff_quest_size_len);
    fscanf(stdin, "%[^\n]s", temp);
    temp[coff_quest_size_len] = '\0';

    i=0;
    j=0;
    while(temp[i]!='\0'){
      if(!isdigit(temp[i])){
        j=1;
        break;
      }
      i++;
    }
  }
  q.no_of_example = (unsigned int) atoi(temp);

  /* Input no of test cases */ 
  j=1;
  while(j == 1){
    printf("\nEnter the no of test cases: ");
    fflush(stdin);
    char_flush(temp, coff_quest_size_len);
    fgets(temp, coff_quest_size, stdin);

    i=0;
    j=0;
    while(temp[i]!='\0'){
      if(!isdigit(temp[i]) && temp[i] != '\n'){
        j=1;
        break;
      }
      i++;
    }
  }
  q.no_of_test_cases = (unsigned int) atoi(temp);

  if (fwrite( &q, sizeof(struct question), 1, outfile) == 0)
    print_err("Contents not written successfully.");

  printf("\nEnter Constraints");

  /* Input time limit */ 
  j=1;
  while(j == 1){
    printf("\nEnter time limit (in milli seconds): ");
    fflush(stdin);
    char_flush(cons.time_limit, coff_quest_size_len);
    fgets(cons.time_limit, coff_quest_size, stdin);

    i=0;
    j=0;
    while(cons.time_limit[i]!='\0'){
      if(!isdigit(cons.time_limit[i]) && cons.time_limit[i] != '\n'){
        j=1;
        break;
      }
      i++;
    }
  }

  printf("Enter the max memory usage (in MB): ");
  fflush(stdin);
  char_flush(cons.memory, coff_quest_size_len);
  fgets(cons.memory, coff_quest_size, stdin);

  printf("Enter CPU percentage usage (DO NOT Write \'%%\') : ");
  fflush(stdin);
  char_flush(cons.cpu, coff_quest_size_len);
  fgets(cons.cpu, coff_quest_size, stdin);

  if(fwrite(&cons, sizeof(struct constraints), 1, outfile) == 0)
    print_err("Contents not written successfully.");

  for (i=0; i<q.no_of_example; i++) {
    printf("\n\nExamples no %d", i+1);
    printf("\n Example input: ");
    fflush(stdin);
    char_flush(examples.input, coff_quest_size_len);
    fgets(examples.input, coff_quest_size, stdin);

    printf(" Example output: ");
    fflush(stdin);
    char_flush(examples.output, coff_quest_size_len);
    fgets(examples.output, coff_quest_size, stdin);

    if(fwrite(&examples, sizeof(struct example), 1, outfile) == 0)
      print_err("Contents not written successfully.");
  }

  for (i=0; i<q.no_of_test_cases; i++) {
    printf("\n\nTest Case no %d", i+1);
    printf("\n Test Case input: ");
    fflush(stdin);
    char_flush(test.input, coff_quest_size_len);
    fgets(test.input, coff_quest_size, stdin);

    printf(" Test Case output: ");
    fflush(stdin);
    char_flush(test.output, coff_quest_size_len);
    fgets(test.output, coff_quest_size, stdin);

    if(fwrite(&test, sizeof(struct test_case), 1, outfile) == 0)
      print_err("Contents not written successfully.");
  }

  fclose(outfile);
  return 0;
}
