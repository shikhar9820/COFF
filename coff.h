#include <limits.h>

#ifndef __COFF_H__  /* COFF_H */

#define __COFF_H__

#define PATH_MAX_len PATH_MAX + 1

int print_err(const char[]);

/* Structure to contain user configuration. - functions.c */
struct {
  char home[PATH_MAX_len];
  char quest_directory[PATH_MAX_len];
  char test_directory[PATH_MAX_len];
}coff_config;

void filename_flush(char[]);
void read_config(void);
void replace_newline_with_null(char[]);

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

#endif /* COOF_H */
