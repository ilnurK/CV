#ifndef GREP_H
#define GREP_H

#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int files;

  unsigned int example : 1;
  unsigned int ign_case : 1;
  unsigned int vert : 1;
  unsigned int count_fit : 1;
  unsigned int list_fit : 1;
  unsigned int num_str : 1;
  unsigned int hide_files : 1;
  unsigned int sup_err : 1;
  unsigned int out_match : 1;
  unsigned int file_reg : 1;
} Tgrep;

typedef struct {
  FILE* main;
  char* name;
  char* reg_name;
  FILE* reg;
} Tfile;

typedef struct {
  int shift;
  int t_shift;
  int temp_match;
  int start;
  int end;
  int len;
} Tregm;

typedef struct {
  int argc;
  int count;
  int* options;
  int* aims;
  int* files;
  char** argv;
  char* str;
  char* aim;
  char* new_aim;
} Tarrs;

#endif
