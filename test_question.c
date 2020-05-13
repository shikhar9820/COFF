/* Stnadard Headers */
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

/* Local Headers */
#include "coff.h"

/* ------------------------------------------------------------------------- */

#define command_flush(x) char_flush(x, PATH_MAX)
#define input_flush(x) char_flush(x, INPUT_MAX)

/* ------------------------------------------------------------------------- */

static int run_question(const char[], const char[]);
char *argv[3];

/* ------------------------------------------------------------------------- */

int test_question(const struct arguments coff_arguments){
  FILE *infile;

  char path[PATH_MAX];

  struct question q;
  struct constraints cons;
  struct example examp;
  struct test_case test;

  unsigned int i;


  for(i=0; i<3; i++)
    argv[i] = malloc(PATH_MAX);

  command_flush(argv[0]);
  command_flush(argv[1]);
  command_flush(argv[2]);

  /*
   * If c, c++, c++11, c++17, then only the first character is 'c',
   * otherwise Coff would have exited during compile time only.
   */
  if(coff_arguments.lang[0] == 'c'){
    strcpy(argv[0], coff_config.null_directory );
    strcat(argv[0], "/coff_testing");
  }

  else{
    free(argv[0]);
    free(argv[1]);
    free(argv[2]);
    return 0;
  }


  /* change current working directory */
  chdir(coff_config.quest_directory);
  if((i = expand_file_path(path, coff_arguments.quest_file)) != 0)
    return i;

  infile = fopen(path, "rb");
  if(infile == NULL){
    print_err("Could not open file.");
    return 1;
  }

  if(fread(&q, sizeof(struct question), 1, infile) == 0)
    print_err("Could not read content.");

  if(fread(&cons, sizeof(struct constraints), 1, infile) == 0)
    print_err("Could not read content.");

  for(i=0; i<q.no_of_examples; i++){
    if(fread(&examp, sizeof(struct example), 1, infile) == 0){
      print_err("Could not read content.");
      continue;
    }
  }

  for(i=0; i<q.no_of_test_cases; i++){
    if(fread(&test, sizeof(struct test_case), 1, infile) == 0){
      print_err("Could not read content.");
      continue;
    }

    printf("\nTestcase %u: ", i+1);
    run_question(test.input, test.output);
  }

  printf("\n");

  fclose(infile);

  free(argv[0]);
  free(argv[1]);
  free(argv[2]);

  return 0;
}

/* ------------------------------------------------------------------------- */

static int run_question(const char test_input[], const char test_output[]){
  char child_output[INPUT_MAX];

  int status;
  int pipe_p_out[2]; // Use this for stdout of parent
  int pipe_c_out[2];  //Use this for stdout of child

  pid_t pid;

  status = pipe(pipe_p_out);
  if(status == -1)
    return errno;

  status = pipe(pipe_c_out);
  if(status == -1)
    return errno;

  pid = fork();

  /* Could not fork */
  if(pid == -1){
    print_err("Cannot fork().");
    return errno;
  }

  else if (pid == 0){
    close(pipe_p_out[1]); //Close write end of p_out
    close(pipe_c_out[0]); //Close read end of c_out

    close(STDIN_FILENO);  //close standard input
    dup2(pipe_p_out[0], STDIN_FILENO); //p_out's read end is stdin

    close(STDOUT_FILENO); //close standard output
    dup2(pipe_c_out[1], STDOUT_FILENO); //p_out's write end is stdout

    if(execvp(argv[0], argv) == -1)
      printf("%s", strerror(errno));

    close(pipe_p_out[0]);
    close(pipe_c_out[1]);
    exit(0);
  }

  else {
    close(pipe_p_out[0]); //Close read end of p_out
    close(pipe_c_out[1]); //Close write end of c_out

    write(pipe_p_out[1], test_input, INPUT_MAX);

    pid = wait(&status); //wait for child to end

    input_flush(child_output);
    while(read(pipe_c_out[0], child_output, INPUT_MAX)>0);

    if(strcmp(child_output, test_output) == 0)
      printf("PASSED");
    else
      printf("FAILED");

    printf("\n  Expected Output: %s", test_output);
    printf("\n  Your Output    : %s\n", child_output);

    close(pipe_c_out[0]);
    close(pipe_p_out[1]);

    return status;
  }




 return 1;
}


/* ------------------------------------------------------------------------- */
