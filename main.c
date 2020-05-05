/* Standard Headers */
#include <stdio.h>
#include <argp.h>

/* Local Headers */
#include "coff.h"

/* ------------------------------------------------------------------------- */
/* ARGP definitions */

/* Version */
const char *argp_program_version = "coff - Offline Judge : 0.01";

/* Documentaion */
static const char usage_doc[] = "\ncoff - Offline Judge\
\n-------------------------------------------------------------------------------\
\n\n If you pass just FILE-NAME,\
\n              ex: coff -s 1.quest -t sol.c\
\n By default coff reads:\
\n - Questions from path: ~/coff/quest\
\n - Answers from path:   ~/coff/ans\
\n\nThe default path can be changed by editing configuration file:\
`~/.coff_config`\
\n\nThe ~/.coff_config should be written as:\
\n    <PROPERTYNAME>\
\n    <PATH>\
\nWhere <PROPERTYNAME> name can be either of \"PATH TO ANSWER\" or \
\"PATH TO QUESTION\" \
and <PATH> is path to directory. Example: \
\n    PATH TO QUESTION\
\n    ~/coff/quest\
\n-------------------------------------------------------------------------------\n";

/* A description of the arguments we accept. */
//static char args_doc[] = "show test lang quest";

/* The options we understand. */
static struct argp_option coff_options[] = {
  {"show",    's', "FILE-NAME/FULL-PATH ",      0,
   "Name of Question File" },
  {"test",    't', "FILE-NAME/FULL-PATH ",      0,
   "Name of your Program/ Solution File" },
  {"lang",    'l', "LANG",      0,  
   "Specify the language of your program. LANG=\n\
[C, C++, C++11, C++17, JAVA, Python2, Python3]\n" },
  {"quest",   'q', "FILE-NAME/FULL-PATH",      0,
   "Name of Question File" },
  { 0 }
};

/* Used by main to communicate with parse_opt. */
struct arguments{
  char *args[4];
  char *test_file;
  char *show_file;
  char *quest_file;
  char *lang;
};

/* Parse a single option. */
static error_t
parse_opt (int key, char *arg, struct argp_state *state){
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */

//  if(state->argc == 1)
//    argp_usage(state);

  struct arguments *coff_arguments = state->input;
  
  switch (key){
    case 's':
      coff_arguments->show_file = arg;
      break;

    case 't':
      coff_arguments->test_file = arg;
      break;

    case 'l':
      coff_arguments->lang = arg;
      break;

    case 'q':
      coff_arguments->quest_file = arg;
      break;

    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

static struct argp coff_argp = { coff_options, parse_opt, 0, usage_doc };
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
int main(int argc, char *argv[]){

  struct arguments coff_arguments;

  /* Default values. */
  coff_arguments.show_file = "-";
  coff_arguments.test_file = "-";
  coff_arguments.lang = "-";
  coff_arguments.quest_file = "-";

  if(argc == 1){
    fprintf(stderr,"coff: Too few arguments"
                   "\n%s\n"
                   "\nTry `coff --help' or `coff --usage' for more information.\n",
                   usage_doc);
    return 0;
  }

  printf("\nReading configuration file.");
  read_config();
  printf("\nSet Default Path for Questions as: %s",
         coff_config.quest_directory);
  printf("\nSet Default Path for Answers as:   %s",
         coff_config.test_directory);
  printf("\n----------------------------------------------------------------"
         "-------------\n");

  /* Parse our arguments; every option seen by parse_opt will
     be reflected in arguments. */
  printf("\n");
  argp_parse (&coff_argp, argc, argv, ARGP_NO_ARGS, 0, &coff_arguments);

  printf("\nTest Mode - Showing arguments");
  printf("\nShow = %s\nTest = %s\nLang = %s\nQuest = %s\n",
         coff_arguments.show_file,
         coff_arguments.test_file,
         coff_arguments.lang,
         coff_arguments.quest_file);

  return 0; 
}
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */

