/* Standard Headers */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <errno.h>

/* Local Headers */
#include "coff.h"

int print_err(const char a[]){
  return fprintf(stderr, "\nError: %s\n", a);
}

/* ------------------------------------------------------------------------- */

void filename_flush(char a[]){
  unsigned int i;

  for(i=0; i<PATH_MAX_len; i++)
    a[i] = '\0';
}

/* ------------------------------------------------------------------------- */

int expand_file_path(char path[], char file[]){
  filename_flush(path);

  if(file[0] == '~'){
    strcpy(path, coff_config.home);
    strcat(path, file+1);
  }

  else if(file[0] == '/'){
    strcpy(path, file);
  }

  else if(file[0] == '.'){
    strcpy(path, file);
  }

  else if(isalnum(file[0])){
    getcwd(path, PATH_MAX);
    strcat(path, "/");
    strcat(path, file);
  }

  else{
    fprintf(stderr, "\nInvalid File Name \"%s\"\n", file);
    return 12;
  }

  if(access(path, F_OK) != 0){
    fprintf(stderr, "\nError: Cannot open file: \"%s\": %s\n",
                   path,
                   strerror(errno));
    return errno;
  }

  return 0;
}

/* ------------------------------------------------------------------------- */

int expand_dir_path(char path[], char dir[]){
  filename_flush(path);

  if(dir[0] == '~'){
    strcpy(path, coff_config.home);
    strcat(path, dir+1);
  }

  else if(dir[0] == '/'){
    strcpy(path, dir);
  }

  else if(dir[0] == '.'){
    strcpy(path, dir);
  }

  else if(isalnum(dir[0])){
    getcwd(path, PATH_MAX);
    strcat(path, "/");
    strcat(path, dir);
  }

  else{
    fprintf(stderr, "\nInvalid Directory Name \"%s\"\n", path);
    return 11;
  }

  DIR *direc = opendir(path);
  if(direc)
    closedir(direc);
  else{
    fprintf(stderr, "\nError: Cannot open directory: \"%s\": %s\n",
                   path,
                   strerror(errno));
    return errno;
  }

  return 0;

}

/* ------------------------------------------------------------------------- */
