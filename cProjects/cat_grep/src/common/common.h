#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  unsigned int err : 1;
  unsigned int stream_end : 1;
  unsigned int last_aims : 1;
  unsigned int aim_found : 1;
  unsigned int matched : 1;
  unsigned int matched_file : 1;
  unsigned int file_reg_supply : 1;
  unsigned int str_end : 1;
  unsigned int already_print : 1;
  unsigned int print_state : 1;
  unsigned int e_aim : 1;
  unsigned int str_emp : 1;
} Tflags;

char* increaseStr(Tflags* flags, char* str, int* buffer);

#endif