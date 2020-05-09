#include <limits.h>

/* ========================================================================= */
#ifndef __COFF_H__  /* COFF_H */
#define __COFF_H__

/* ========================================================================= */
/* All Declarations start from here. */

#define PATH_MAX_len PATH_MAX + 1

/* ========================================================================= */
/* Coff Questions and Answers */
#define coff_quest_name_size 100
#define coff_quest_size 1000

#define coff_quest_name_size_len  coff_quest_name_size + 1
#define coff_quest_size_len       coff_quest_size + 1

/*
 * The pattern is to define string size as "xyz_size_len" and the input size
 * in string will be of size "xyz_size".
 * The "xyz_size_len" is just 1 byte extra than "xyz_size" to store null char.
 */

/* Structure for questions*/
struct question {
  char name[coff_quest_name_size_len];
  char question[coff_quest_size_len];
  unsigned int no_of_example;
  unsigned int no_of_test_cases;
};

struct test_case {
  char input[coff_quest_size_len];
  char output[coff_quest_size_len];
};

struct constraints {
  char time_limit[coff_quest_size_len];
  char memory[coff_quest_size_len];
  char cpu[coff_quest_size_len];

};

struct example {
  char input[coff_quest_size_len];
  char output[coff_quest_size_len];
};

/* ========================================================================= */
/* Structure to contain user configuration. - functions.c */
struct {
  char home[PATH_MAX_len];
  char quest_directory[PATH_MAX_len];
  char test_directory[PATH_MAX_len];
}coff_config;

/* ========================================================================= */
void char_flush(char[], unsigned int);
void read_config(void);
int print_err(const char[]);

/* ========================================================================= */
/*
 * Defined in functions.c
 *
 * The exapnd functions derive the original path out of relative one.
 * for ex, user types: ~/xyz
 * Hence, the full path is: /home/abc/xyz, where abc is home folder of user.
 * Below both functions return 0 only on success.
 */
int expand_file_path(char[] /*dest*/, char[]/*source*/);
int expand_dir_path(char[] /*dest*/, char[]/*source*/);

/* ========================================================================= */
#endif /* COOF_H */
/* ========================================================================= */
