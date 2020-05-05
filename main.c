/* Standard Headers */
#include <stdio.h>
#include <argp.h>

/* Local Headers */
#include "coff.h"


static const char config_doc[]="\
\n-------------------------------------------------------------------------------\
\n\n If you pass just filename to options,\
\n              ex: coff -s 1.quest -t sol.c\
\n   by default coff reads:\
\n   - Questions from path: ~/coff/quest\
\n   - Answers from path:   ~/coff/ans\
\n\n The default path can be changed by editing configuration \
file: `~/.coff_config`\
\n\n The ~/.coff_config should be written as:\
\n        <PROPERTYNAME>\
\n        <PATH>\
\n    Where <PROPERTYNAME> name can be either of \
\n    \"PATH TO ANSWER\" or \"PATH TO QUESTION\" \
\n    and <PATH> is path to directory.\
\n      Example: \
\n        1 |PATH TO QUESTION\
\n        2 |~/coff/quest\
\n-------------------------------------------------------------------------------\n";

/* ------------------------------------------------------------------------- */
/* ARGP definitions */

/* Version */
const char *argp_program_version = "coff - Offline Judge : 0.01";

/* Documentaion */
static const char usage_doc[] = "\ncoff - Offline Judge";

/* A description of the arguments we accept. */
//static char args_doc[] = "show test lang quest";

/* The options we understand. */
static struct argp_option coff_options[] = {
  { /* Option 1 */
    "show",
    's',
    "FILE/PATH ",
    0,
    "Prints Question "
  },

  { /* Option 2 */
    "test",
    't',
    "FILE/PATH ",
    0,
    "Program/ Solution File"
  },

  { /* Option 3 */
    "lang",
    'l',
    "LANG",
    0,  
    "Specify the language of your program. LANG=\n\
[C, C++, C++11, C++17, JAVA, Python2, Python3]" 
  },

  { /* Option 4 */
    "quest",
    'q',
    "FILE/PATH",
    0,
    "Used with --test for Evaluation"
  },

  { /* Option 5 */
    "about-config",
    'a',
    0,
    0,
    "How to modify config file?"
  },

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
    case 'a':
      printf("%s", config_doc);
      break;
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

