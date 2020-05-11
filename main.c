/* Standard Headers */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <argp.h>

/* Local Headers */
#include "coff.h"

/* ------------------------------------------------------------------------- */

#define command_flush(x) char_flush(x, PATH_MAX)

/* ------------------------------------------------------------------------- */

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
    "Prints Question\n"
  },

  { /* Option 2 */
    "test",
    't',
    "FILE/PATH ",
    0,
    "Program/ Solution File\n"
  },

  { /* Option 3 */
    "lang",
    'l',
    "LANG",
    0,  
    "Specify the language of your program. LANG=\n\
[C, C++, C++11, C++17, JAVA, Python2, Python3]\n" 
  },

  { /* Option 4 */
    "quest",
    'q',
    "FILE/PATH",
    0,
    "Used with --test for Evaluation\n"
  },

  { /* Option 5 */
    "flag",
    'f',
    "FLAG",
    0,
    "C/C++ program may need linked flags like,\
\"-lpthread\", \"-lncurses\", \"-lm\", etc. \
They should be written inside double quotes.\n"
  },

  { /* Option 6 */
    "doc",
    'd',
    0,
    0,
    "Documentation\n"
  },

  { 0 }
};

/* Parse a single option. */
static error_t
parse_opt (int key, char *arg, struct argp_state *state){
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */

  struct arguments *coff_arguments = state->input;
  unsigned int i;
  
  switch (key){
    case 'f':
      coff_arguments->flag = arg;
      coff_config.opt |= 0x10;
      break;

    case 'd':
      printf("%s", config_doc);
      break;

    case 's':
      coff_arguments->quest_file = arg;
      coff_config.opt |= 0x1;
      coff_config.opt |= 0x8;
      break;

    case 't':
      coff_arguments->test_file = arg;
      coff_config.opt |= 0x2;
      break;

    case 'l':
      for(i=0; arg[i] != '\0'; i++)
        arg[i] = tolower(arg[i]);
      coff_arguments->lang = arg;
      coff_config.opt |= 0x4;
      break;

    case 'q':
      coff_arguments->quest_file = arg;
      coff_config.opt |= 0x8;
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

  int status; /* value returned by functions */

  struct arguments coff_arguments;

  /* Default values. */
  coff_arguments.test_file = "-";
  coff_arguments.lang = "-";
  coff_arguments.quest_file = "-";
  coff_arguments.flag = "-";

  coff_config.opt = 0x0;

  if(argc == 1){
    fprintf(stderr,"coff: Too few arguments"
                   "\n%s\n"
                   "\nTry `coff --help' or `coff --usage' for more information.\n",
                   usage_doc);
    return 0;
  }

  /* Parse our arguments; every option seen by parse_opt will
     be reflected in arguments. */
  printf("\n");
  argp_parse (&coff_argp, argc, argv, ARGP_NO_ARGS, 0, &coff_arguments);

  read_config();

  printf("\nTest Mode - Showing arguments");
  if( coff_config.opt & 0x1 )
    printf("\nShow = %s", coff_arguments.quest_file);
  if( coff_config.opt & 0x2 )
    printf("\nTest = %s", coff_arguments.test_file);
  if( coff_config.opt & 0x4 )
    printf("\nLang = %s", coff_arguments.lang);
  if( coff_config.opt & 0x8 )
    printf("\nQuest = %s", coff_arguments.quest_file);
  if( coff_config.opt & 0x10 )
    printf("\nFlag = %s", coff_arguments.flag);

  if( coff_config.opt & 0x1 )
    show_question(coff_arguments.quest_file);

  if( !((coff_config.opt & 0xE)^0xE) ){
    status = compile_test(coff_arguments);
    if(status)
      exit(status);
  }





  printf("\n");
  return 0; 
}
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
