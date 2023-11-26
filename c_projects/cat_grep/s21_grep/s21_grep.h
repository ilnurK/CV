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
  FILE *main;
  char *name;
  char *reg_name;
  FILE *reg;
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
  int *options;
  int *aims;
  int *files;
  char **argv;
  char *str;
  char *aim;
  char *new_aim;
} Tarrs;

#include "../common/common.h"

void setTo0(int *arr, int len);

void checker(Tgrep *grep, Tarrs *arr, Tflags *flags);
void locateOption(Tgrep *grep, Tarrs *arr, Tflags *flags, int i);
void locateAimAndFile(Tgrep *grep, Tarrs *arr, Tflags *flags, int i);
void optionE(Tarrs *arr, Tflags *flags, int len, int i, int j);

void filesOpening(Tgrep *grep, Tarrs *arr, Tflags *flags);
void fileCycle(Tgrep grep, Tarrs *arr, Tfile file, Tflags *flags, int i);
void printFileError(Tgrep grep, char *filename);

char *getString(Tfile file, Tflags *flags);
char *increaseStr(Tflags *flags, char *str, int *buffer);
void strCycle(Tgrep grep, Tarrs *arr, Tfile file, Tflags *flags);
void aimsCycle(Tgrep grep, Tarrs *arr, Tfile file, Tflags *flags, Tregm *rm);
void fileReg(Tgrep grep, Tarrs *arr, Tfile file, Tflags *flags, Tregm *rm);
void isManyMatched(Tgrep grep, Tarrs *arr, Tflags *flags, Tregm *rm);
void findClosestMatch(Tregm *rm, regmatch_t match);
void printStates(Tgrep grep, Tarrs *arr, Tfile file, Tflags *flags, Tregm *rm);
void printer(Tgrep grep, Tarrs *arr, Tfile file, Tflags *flags, Tregm rm);
void printAlter(Tgrep grep, Tarrs arr, Tfile file, Tflags flags, int i);

#endif
