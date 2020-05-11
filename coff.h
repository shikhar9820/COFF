#include <limits.h>
#include <stdint.h>

/* ========================================================================= */
#ifndef __COFF_H__  /* COFF_H */
#define __COFF_H__

/* ========================================================================= */
/* All Declarations start from here. */

/* Coff Questions and Answers */
#define INPUT_MAX 101  /* Max char limit for inputs */
#define QUEST_MAX 1001 /* Max char limit for question */

/*
 * The pattern is to define string size as "xyz_size_len" and the input size
 * in string will be of size "xyz_size".
 * The "xyz_size_len" is just 1 byte extra than "xyz_size" to store null char.
 */

/* Structure for questions*/
struct question {
  char name[INPUT_MAX];
  char question[QUEST_MAX];
  unsigned int no_of_examples;
  unsigned int no_of_test_cases;
};

struct test_case {
  char input[INPUT_MAX];
  char output[INPUT_MAX];
};

struct constraints {
  char time_limit[INPUT_MAX];
  char memory[INPUT_MAX];
  char cpu[INPUT_MAX];

};

struct example {
  char input[INPUT_MAX];
  char output[INPUT_MAX];
};

/* ========================================================================= */
/* Structure to contain user configuration. - functions.c
 * opt:
 * - 1  = show
 * - 2  = test
 * - 4  = lang
 * - 8  = quest
 * - 16 = flag
 */

struct {
  char cwd[PATH_MAX];
  char home[PATH_MAX];
  char quest_directory[PATH_MAX];
  char test_directory[PATH_MAX];
  uint8_t opt : 5;
}coff_config;

/* ========================================================================= */
/* Used by main to communicate with parse_opt. */
struct arguments{
  char *test_file;
  char *quest_file;
  char *lang;
  char *flag;
};

/* ========================================================================= */
void char_flush(char[], unsigned int);
void read_config(void);

/* Below functions return zero on success */
int print_err(const char[]);
int show_question(const char[]);
int compile_test(const struct arguments);

/* ========================================================================= */
/*
 * Defined in functions.c
 *
 * The exapnd functions derive the original path out of relative one.
 * for ex, user types: ~/xyz
 * Hence, the full path is: /home/abc/xyz, where abc is home folder of user.
 * Below both functions return 0 only on success.
 */
int expand_file_path(char[] /*dest*/, const char[]/*source*/);
int expand_dir_path(char[] /*dest*/,  const char[]/*source*/);

/* ========================================================================= */
#endif /* COOF_H */
/* ========================================================================= */
