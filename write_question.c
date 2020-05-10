/* Standard Headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Local Headers */
#include "coff.h"

/* ------------------------------------------------------------------------- */

/* It's purpose is to read string of size 'i' and store into char 'a'
 * and make sure that no '\n' is present at the end due to 'fgets'.
 */
static void read_string(char a[], unsigned int i){
  char_flush(a, i);
  fgets(a, i, stdin);
  for(i=0; a[i] != '\0'; i++);
  i--;
  if(a[i] == '\n')
    a[i] = '\0';
}

/* ------------------------------------------------------------------------- */

#define read_input_string(x) read_string(x, INPUT_MAX)
#define read_quest_string(x) read_string(x, QUEST_MAX)

/* ------------------------------------------------------------------------- */

/* It's purpose is to read a number in the form of string & store it in 'a' */
static void read_int_string(char a[], const char out[]){
  int j, i;
  j=1;
  while(j == 1){
    printf("%s", out);
    read_input_string(a);

    j=0;
    i=0;
    while(a[i] != '\0'){
      if(!isdigit(a[i])){
        j=1;
        break;
      }
      i++;
    }
  }
}
/* ------------------------------------------------------------------------- */

int main(){
  FILE *outfile;
  char file[PATH_MAX];
  char temp[INPUT_MAX];
  struct question q;
  struct test_case test;
  struct constraints cons;
  struct example examp;
  unsigned int i;

  read_config();

  char_flush(file, PATH_MAX);
  strcpy(file, coff_config.quest_directory);
  strcat(file, "/newQuestion.quest");
  printf("\nThe Question will be written in: %s\n", file);

  remove(file);

  outfile = fopen(file, "wb");
  if (outfile == NULL){
    print_err("Could not open file.");
    exit(1);
  }

  printf("\nEnter the Question-Name (Max %u characters): ",
         INPUT_MAX-1);
  read_input_string(q.name);
//  printf("inName: %s", q.name);

  printf("\nEnter the Question-Statement (Hit Enter when done writing) (Max \
%u characters)\nStart: ",
         QUEST_MAX-1);
  read_quest_string(q.question);
//  printf("inQuest: %s", q.question);

  read_int_string(temp, "Enter the no of examples: ");
  q.no_of_examples = (unsigned int) atoi(temp);

  read_int_string(temp, "Enter the no of test cases: ");
  q.no_of_test_cases = (unsigned int) atoi(temp);

//  printf("in%u  %u", q.no_of_examples, q.no_of_test_cases);

  if (fwrite( &q, sizeof(struct question), 1, outfile) == 0)
    print_err("Contents not written successfully.");

  printf("\nEnter Constraints");
  read_int_string(cons.time_limit, "\nEnter time limit (in milli seconds): " );
  read_int_string(cons.memory, "\nEnter the max memory usage (in MB): " );
  read_int_string(cons.cpu, "\nEnter CPU percentage usage (DO NOT\
 Write \'%%\') : " );

  if(fwrite(&cons, sizeof(struct constraints), 1, outfile) == 0)
    print_err("Contents not written successfully.");

  for (i=0; i<q.no_of_examples; i++) {
    printf("\n\nExamples no %d", i+1);
    printf("\n Example input:  ");
    read_input_string(examp.input);
    printf(" Example output: ");
    read_input_string(examp.output);
    if(fwrite(&examp, sizeof(struct example), 1, outfile) == 0)
      print_err("Contents not written successfully.");
  }

  printf("\n----------------------------------------------------------------");

  for (i=0; i<q.no_of_test_cases; i++) {
    printf("\n\nTest Case no %d", i+1);
    printf("\n Test Case input: ");
    read_input_string(test.input);
    printf(" Test Case output: ");
    read_input_string(test.output);
    if(fwrite(&test, sizeof(struct test_case), 1, outfile) == 0)
      print_err("Contents not written successfully.");
  }

  fclose(outfile);
}
